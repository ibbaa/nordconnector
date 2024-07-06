#include "common.h"
#include "Main.h"
#include "args/CommandLineParser.h"
#include "config/CredentialsHelper.h"
#include "config/OVPNConfigReader.h"
#include "server/AsyncHTTPDownloader.h"
#include "server/ServerSelector.h"
#include "ovpn/OVPNConnector.h"
#include "util/Output.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "Poco/Path.h"

int Main::main(int argc, char *argv[]) {
    CommandLineParser parser;
    Options options = parser.parse(argc, argv);
    if (!options.validate()) {
        Output::err_output(options.get_validation_message());
        return RETURN_CODES::VALIDATION_ERROR;
    }
    if (!is_root()) {
        Output::err_output("Superuser privileges are required. Please use sudo to run this program.\n");
        return RETURN_CODES::PRIVILEGES_ERROR;
    }
    Output::output(options.describe(), options.get_verbose());
    if (!AsyncHTTPDownloader::initSSL()) {
        return RETURN_CODES::SSL_INIT_ERROR;
    }
    AsyncHTTPDownloader downloader;
    std::future<std::string> stat_ovpn = downloader.download(options.get_ovpn(), options.get_verbose());
    Server server = select_provided_server(options);
    std::string server_data = "";
    if (!server.is_provided()) {
        server_data = download_servers(options);
        server = select_server(server_data, options);
    }
    log_server(server, options);
    const std::string &ovpn_data = get_from_future(stat_ovpn);
    if (ovpn_data.empty()) {
        Output::err_output("Download error\n");
        return RETURN_CODES::DOWNLOAD_ERROR;
    }
    umask(0077);
    OVPNConfigReader reader;
    std::string ovpn_config = reader.extract_config(ovpn_data, server.get_address(), options.get_verbose());
    int retry = OVPN_ERROR_RETRY;
    while (ovpn_config.empty() && retry > 0 && !server.is_provided()) {
        Output::output("Error retrieving openvpn configuration\n", options.get_verbose());
        Output::output("Retry...\n", options.get_verbose());
        server = select_server(server_data, options);
        log_server(server, options);
        ovpn_config = reader.extract_config(ovpn_data, server.get_address(), options.get_verbose());
        retry--;
    }
    if (ovpn_config.empty()) {
        Output::err_output("Error retrieving openvpn configuration\n");
        return RETURN_CODES::OVPN_CONFIG_ERROR;
    }
    CredentialsHelper cred_helper;
    const std::string &ovpn_cred = cred_helper.provide_ovpn_credentials(server.get_address(), options.get_user(), options.get_password(), options.get_verbose());
    if (ovpn_cred.empty()) {
        Output::err_output("Error providing ovpn credentials\n");
        Output::delete_file(ovpn_config);
        return RETURN_CODES::OVPN_CONFIG_ERROR;
    }
    OVPNConnector connector;
    connector.connect(ovpn_config, ovpn_cred, options.get_daemon(), options.get_passthrough(), options.get_verbose());
    Output::delete_file(ovpn_config);
    Output::delete_file(ovpn_cred);
    return RETURN_CODES::OK;
}

bool Main::is_root() {
    return geteuid() == 0;
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

Server Main::select_provided_server(const Options &options) {
    if (options.get_server()) {
        std::vector<std::string> countries = options.get_countries();
        if (countries.size() <= 0) {
            Output::err_output("-s/--server provided but no server specified\n");
            exit(RETURN_CODES::GENERAL_ERROR);
        }
        return Server { countries[0], -1, true };
    }
    return Server { };
}

std::string Main::download_servers(const Options &options) {
    AsyncHTTPDownloader downloader;
    std::future<std::string> stat_result = downloader.download(options.get_stat(), options.get_verbose());
    std::string stat_data = get_from_future(stat_result);
    if (stat_data.empty()) {
        Output::err_output("Download error\n");
        exit(RETURN_CODES::DOWNLOAD_ERROR);
    }
    return stat_data;
}

Server Main::select_server(const std::string stat_data, const Options &options) {
    ServerSelector selector;
    Server server = selector.select(stat_data, options.get_countries(), options.get_loadtolerance(), options.get_maxload(), options.get_verbose());
    if (server.get_address().empty()) {
        Output::err_output("Error retrieving suitable server\n");
        exit(RETURN_CODES::SELECT_ERROR);
    }
    return server;
}

void Main::log_server(const Server &server, const Options &options) {
    if (server.get_load() >= 0) {
        Output::output("Selected server: " + server.get_address() + " with current load factor of " + std::to_string(server.get_load()) + "\n", options.get_verbose());
    } else {
        Output::output("Selected server: " + server.get_address() + "\n", options.get_verbose());
    }
}
