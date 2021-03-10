#include "common.h"
#include <Main.h>
#include "args/CommandLineParser.h"
#include "server/AsyncHTTPDownloader.h"
#include "server/ServerSelector.h"
#include <stdlib.h>
#include <iostream>
#include <string>

int Main::main(int argc, char *argv[]) {
    CommandLineParser parser;
    NVPNOptions options = parser.parse(argc, argv);
    if (!options.validate()) {
        std::cerr << options.get_validation_message();
        return RETURN_CODES::VALIDATION_ERROR;
    }
    output(options, options.describe());
    if (!AsyncHTTPDownloader::initSSL()) {
        return RETURN_CODES::SSL_INIT_ERROR;
    }
    AsyncHTTPDownloader downloader;
    std::future<std::string> stat_ovpn = downloader.download(options.get_ovpn(), options.get_verbose());
    const std::string &server = select_server(options);
    output(options, "Selected server: " + server + "\n");
    const std::string &ovpn_data = get_from_future(stat_ovpn);
    if (ovpn_data.empty()) {
        std::cerr << "Download error\n";
        return RETURN_CODES::DOWNLOAD_ERROR;
    }
    return RETURN_CODES::OK;
}

void Main::output(const NVPNOptions &options, const std::string &message) {
    if (options.get_verbose()) {
        std::cout << message;
    }
}

std::string Main::get_from_future(std::future<std::string> &data) {
    std::future_status status = std::future_status::deferred;
    do {
        std::future_status status = data.wait_for(std::chrono::seconds(DOWNLOAD_TIMEOUT));
        if (status == std::future_status::timeout) {
            std::cerr << "Timeout while waiting for the download to complete\n";
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
            std::cerr << "-s/--server provided but no server specified\n";
            exit(RETURN_CODES::GENERAL_ERROR);
        }
        return countries[0];
    }
    AsyncHTTPDownloader downloader;
    std::future<std::string> stat_result = downloader.download(options.get_stat(), options.get_verbose());
    const std::string &stat_data = get_from_future(stat_result);
    if (stat_data.empty()) {
        std::cerr << "Download error\n";
        exit(RETURN_CODES::DOWNLOAD_ERROR);
    }
    ServerSelector selector;
    std::string server = selector.select(stat_data, options.get_countries(), options.get_verbose());
    if (server.empty()) {
        std::cerr << "Error retrieving suitable server\n";
        exit(RETURN_CODES::SELECT_ERROR);
    }
    return server;
}
