#include "common.h"
#include "args/CommandLineParser.h"
#include "util/Output.h"
#include <stdlib.h>
#include <stdio.h>

Options CommandLineParser::parse(int argc, char *argv[]) {
    std::string version("nordc version " + VERSION + ", build time " + __DATE__ + " " + __TIME__);
    cxxopts::Options options(argv[0], version);
    options.add_options()("s,server", "connect to a specific server by name, otherwise the server is chosen based on a list of countries", cxxopts::value<bool>()->default_value("false"))("d,daemon",
            "run openvpn in daemon mode", cxxopts::value<bool>()->default_value("false"))("h,help", "Print help")("e,version", "Print version")("o,ovpn",
            "Url to retrieve openvpn server configuration", cxxopts::value<std::string>()->default_value(OVPN_URL_DEFAULT))("a,stat", "Url to retrieve server statistics",
            cxxopts::value<std::string>()->default_value(STAT_URL_DEFAULT))("u,user", "User", cxxopts::value<std::string>())("p,password", "Password", cxxopts::value<std::string>())("t,passthrough",
            "command line options directly passed to openvpn", cxxopts::value<std::string>())("l,loadtolerance", "acceptable load tolerance (0 to 100)", cxxopts::value<int>()->default_value("5"))(
            "m,maxload", "maximum acceptable load (0 to 100)", cxxopts::value<int>()->default_value("70"))("c,tcp", "Use TCP instead of UDP output", cxxopts::value<bool>()->default_value("false"))(
            "v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))("countries", "", cxxopts::value<std::vector<std::string>>());
    options.parse_positional("countries");
    options.positional_help("list of countries to connect (separated by blank), if -s is provided a specific server by name");
    try {
        cxxopts::ParseResult result = options.parse(argc, argv);
        if (result.count("help")) {
            Output::output(options.help(), true);
            exit(RETURN_CODES::OK);
        }
        if (result.count("version")) {
            Output::output(version + "\n", true);
            exit(RETURN_CODES::OK);
        }
        return Options(get_server(result), get_daemon(result), get_countries(result), get_ovpn(result), get_stat(result), get_user(result), get_password(result), get_passthrough(result),
                get_loadtolerance(result), get_maxload(result), get_tcp(result), get_verbose(result));
    } catch (const cxxopts::exceptions::exception &exc) {
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

bool CommandLineParser::get_daemon(const cxxopts::ParseResult &result) const {
    if (result.count("daemon")) {
        return result["daemon"].as<bool>();
    }
    return false;
}

bool CommandLineParser::get_tcp(const cxxopts::ParseResult &result) const {
    if (result.count("tcp")) {
        return result["tcp"].as<bool>();
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

std::string CommandLineParser::get_passthrough(const cxxopts::ParseResult &result) const {
    if (result.count("passthrough")) {
        return result["passthrough"].as<std::string>();
    }
    return "";
}

int CommandLineParser::get_loadtolerance(const cxxopts::ParseResult &result) const {
    return result["loadtolerance"].as<int>();
}

int CommandLineParser::get_maxload(const cxxopts::ParseResult &result) const {
    return result["maxload"].as<int>();
}
