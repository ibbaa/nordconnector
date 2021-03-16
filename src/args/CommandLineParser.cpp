#include "common.h"
#include "args/CommandLineParser.h"
#include "util/Output.h"
#include <stdlib.h>

NVPNOptions CommandLineParser::parse(int argc, char *argv[]) {
    cxxopts::Options options(argv[0], "Alternative NORDVPN connection tool");
    options.add_options()("s,server", "connect to a specific server by name, otherwise the server is chosen based on a list of countries", cxxopts::value<bool>()->default_value("false"))("h,help",
            "Print help")("o,ovpn", "Url to retrieve openvpn server configuration", cxxopts::value<std::string>()->default_value(OVPN_URL_DEFAULT))("a,stat", "Url to retrieve server statistics",
            cxxopts::value<std::string>()->default_value(STAT_URL_DEFAULT))("u,user", "User", cxxopts::value<std::string>())("p,password", "Password", cxxopts::value<std::string>())("v,verbose",
            "Verbose output", cxxopts::value<bool>()->default_value("false"))("countries", "", cxxopts::value<std::vector<std::string>>());
    options.parse_positional("countries");
    options.positional_help("list of countries to connect (separated by blank), if -s is provided a specific server by name");
    try {
        cxxopts::ParseResult result = options.parse(argc, argv);
        if (result.count("help")) {
            Output::output(options.help(), true);
            exit(RETURN_CODES::OK);
        }
        return NVPNOptions(get_server(result), get_countries(result), get_ovpn(result), get_stat(result), get_user(result), get_password(result), get_verbose(result));
    } catch (const cxxopts::OptionException &exc) {
        Output::err_output("Command line option error: " + std::string(exc.what()) + "\n");
        exit(RETURN_CODES::PARSE_ERROR);
    } catch (...) {
        Output::err_output("Command line option error.\n");
        exit(RETURN_CODES::PARSE_ERROR);
    }
}

bool CommandLineParser::get_server(const cxxopts::ParseResult &result) const {
    if (result.count("server")) {
        return result["server"].as<bool>();
    }
    return false;
}

bool CommandLineParser::get_verbose(const cxxopts::ParseResult &result) const {
    if (result.count("verbose")) {
        return result["verbose"].as<bool>();
    }
    return false;
}

std::vector<std::string> CommandLineParser::get_countries(const cxxopts::ParseResult &result) const {
    if (result.count("countries")) {
        return result["countries"].as<std::vector<std::string>>();
    }
    return std::vector<std::string>();
}

std::string CommandLineParser::get_ovpn(const cxxopts::ParseResult &result) const {
    return result["ovpn"].as<std::string>();
}

std::string CommandLineParser::get_stat(const cxxopts::ParseResult &result) const {
    return result["stat"].as<std::string>();
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
