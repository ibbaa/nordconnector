#include "args/CommandLineParser.h"
#include <stdlib.h>

#define OVPN_URL_DEFAULT "https://downloads.nordcdn.com/configs/archives/servers/ovpn.zip"
#define STAT_URL_DEFAULT "https://nordvpn.com/api/server/stats"

NVPNOptions CommandLineParser::parse(int argc, char *argv[]) {
    cxxopts::Options options(argv[0], "Alternative NORDVPN connection tool");
    options.add_options()("s,server", "Server to connect", cxxopts::value<std::string>())("c,countries", "List of countries to connect, comma separated", cxxopts::value<std::vector<std::string>>())(
            "h,help", "Print help")("o,ovpn", "Url to retrieve openvpn server configuration", cxxopts::value<std::string>()->default_value(OVPN_URL_DEFAULT))("a,stat",
            "Url to retrieve server statistics", cxxopts::value<std::string>()->default_value(STAT_URL_DEFAULT))("u,user", "User", cxxopts::value<std::string>())("p,password", "Password",
            cxxopts::value<std::string>());
    cxxopts::ParseResult result = options.parse(argc, argv);
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    return NVPNOptions(get_server(result), get_countries(result), get_ovpn(result), get_stat(result), get_user(result), get_password(result));
}

std::string CommandLineParser::get_server(const cxxopts::ParseResult &result) const {
    if (result.count("server")) {
        return result["server"].as<std::string>();
    }
    return "";
}

std::vector<std::string> CommandLineParser::get_countries(const cxxopts::ParseResult &result) const {
    if (result.count("countries")) {
        return result["countries"].as<std::vector<std::string>>();
    }
    return std::vector<std::string>();
}

std::string CommandLineParser::get_ovpn(const cxxopts::ParseResult &result) const {
    if (result.count("ovpn")) {
        return result["ovpn"].as<std::string>();
    }
    return "";
}

std::string CommandLineParser::get_stat(const cxxopts::ParseResult &result) const {
    if (result.count("stat")) {
        return result["stat"].as<std::string>();
    }
    return "";
}

std::string CommandLineParser::get_user(const cxxopts::ParseResult &result) const {
    if (result.count("user")) {
        return result["user"].as<std::string>();
    }
    return "";
}

std::string CommandLineParser::get_password(const cxxopts::ParseResult &result) const {
    if (result.count("password")) {
        return result["password"].as<std::string>();
    }
    return "";
}
