#include "common.h"
#include "Main.h"
#include "args/CommandLineParser.h"
#include "config/CredentialsHelper.h"
#include "config/OVPNConfigReader.h"
#include "server/AsyncHTTPDownloader.h"
#include "server/ServerSelector.h"
#include "util/Output.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Poco/Path.h"

int Main::main(int argc, char *argv[]) {
    CommandLineParser parser;
    NVPNOptions options = parser.parse(argc, argv);
    if (!options.validate()) {
        Output::err_output(options.get_validation_message());
        return RETURN_CODES::VALIDATION_ERROR;
    }
    Output::output(options.describe(), options.get_verbose());
    if (!AsyncHTTPDownloader::initSSL()) {
        return RETURN_CODES::SSL_INIT_ERROR;
    }
    AsyncHTTPDownloader downloader;
    std::future<std::string> stat_ovpn = downloader.download(options.get_ovpn(), options.get_verbose());
    const std::string &server = select_server(options);
    Output::output("Selected server: " + server + "\n", options.get_verbose());
    const std::string &ovpn_data = get_from_future(stat_ovpn);
    if (ovpn_data.empty()) {
        Output::err_output("Download error\n");
        return RETURN_CODES::DOWNLOAD_ERROR;
    }
    OVPNConfigReader reader;
    const std::string &ovpn_config = reader.extract_config(ovpn_data, server, options.get_verbose());
    if (ovpn_config.empty()) {
        Output::err_output("Error retrieving openvpn configuration\n");
        return RETURN_CODES::OVPN_CONFIG_ERROR;
    }
    CredentialsHelper cred_helper;
    const std::string &ovpn_cred = cred_helper.provide_ovpn_credentials(server, options.get_user(), options.get_password(), options.get_verbose());
    if (ovpn_cred.empty()) {
        Output::err_output("Error providing ovpn credentials\n");
        return RETURN_CODES::OVPN_CONFIG_ERROR;
    }
    std::string ovpncmd = "openvpn --config " + ovpn_config + " --auth-user-pass " + ovpn_cred;
    Output::output(ovpncmd + "\n", options.get_verbose());
    int ovpnresult = system(ovpncmd.c_str());
    Output::output("openvpn result code: " + std::to_string(ovpnresult) + "\n", options.get_verbose());
    Output::delete_file(ovpn_config);
    Output::delete_file(ovpn_cred);
    return RETURN_CODES::OK;
}

std::string Main::get_from_future(std::future<std::string> &data) {
    std::future_status status = std::future_status::deferred;
    do {
        std::future_status status = data.wait_for(std::chrono::seconds(DOWNLOAD_TIMEOUT));
        if (status == std::future_status::timeout) {
            Output::err_output("Timeout while waiting for the download to complete\n");
            exit(RETURN_CODES::TIMEOUT);
        } else if (status == std::future_status::ready) {
            return data.get();
        }

    } while (status != std::future_status::ready && status != std::future_status::timeout);
    return "";
}

std::string Main::select_server(const NVPNOptions &options) {
    if (options.get_server()) {
        std::vector<std::string> countries = options.get_countries();
        if (countries.size() <= 0) {
            Output::err_output("-s/--server provided but no server specified\n");
            exit(RETURN_CODES::GENERAL_ERROR);
        }
        return countries[0];
    }
    AsyncHTTPDownloader downloader;
    std::future<std::string> stat_result = downloader.download(options.get_stat(), options.get_verbose());
    const std::string &stat_data = get_from_future(stat_result);
    if (stat_data.empty()) {
        Output::err_output("Download error\n");
        exit(RETURN_CODES::DOWNLOAD_ERROR);
    }
    ServerSelector selector;
    std::string server = selector.select(stat_data, options.get_countries(), options.get_verbose());
    if (server.empty()) {
        Output::err_output("Error retrieving suitable server\n");
        exit(RETURN_CODES::SELECT_ERROR);
    }
    return server;
}
