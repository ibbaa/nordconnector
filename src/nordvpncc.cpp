#include "common.h"
#include "args/CommandLineParser.h"
#include "server/AsyncHTTPDownloader.h"
#include <iostream>
#include <string>
#include <Poco/Timestamp.h>
#include <Poco/Timezone.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>

void output(const NVPNOptions &options, const std::string &message);

int main(int argc, char *argv[]) {
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
    std::future<std::string> stat_result = downloader.download(options.get_stat(), options.get_verbose());
    std::future<std::string> stat_ovpn = downloader.download(options.get_ovpn(), options.get_verbose());
    const std::string &stat_data = stat_result.get();
    if (stat_data.empty()) {
        std::cerr << "Download error\n";
        return RETURN_CODES::DOWNLOAD_ERROR;
    }
    const std::string &ovpn_data = stat_ovpn.get();
    if (ovpn_data.empty()) {
        std::cerr << "Download error\n";
        return RETURN_CODES::DOWNLOAD_ERROR;
    }
    return RETURN_CODES::OK;
}

void output(const NVPNOptions &options, const std::string &message) {
    if (options.get_verbose()) {
        std::cout << message;
    }
}
