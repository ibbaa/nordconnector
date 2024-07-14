#ifndef SRC_ARGS_COMMANDLINEPARSER_H_
#define SRC_ARGS_COMMANDLINEPARSER_H_

#include <args/Options.h>
#include <string>
#include <vector>
#include "cxxopts.hpp"

#define OVPN_URL_DEFAULT "https://downloads.nordcdn.com/configs/files/ovpn_legacy/servers/"
#define STAT_URL_DEFAULT "https://api.nordvpn.com/v1/servers?limit=3000&filters[servers.status]=online&fields[servers.hostname]&fields[servers.load]"

class CommandLineParser {
    public:
        Options parse(int argc, char *argv[]);
    private:
        bool get_server(const cxxopts::ParseResult &result) const;
        bool get_daemon(const cxxopts::ParseResult &result) const;
        std::vector<std::string> get_countries(const cxxopts::ParseResult &result) const;
        std::string get_ovpn(const cxxopts::ParseResult &result) const;
        std::string get_stat(const cxxopts::ParseResult &result) const;
        std::string get_user(const cxxopts::ParseResult &result) const;
        std::string get_password(const cxxopts::ParseResult &result) const;
        std::string get_passthrough(const cxxopts::ParseResult &result) const;
        int get_loadtolerance(const cxxopts::ParseResult &result) const;
        int get_maxload(const cxxopts::ParseResult &result) const;
        bool get_tcp(const cxxopts::ParseResult &result) const;
        bool get_verbose(const cxxopts::ParseResult &result) const;
};

#endif /* SRC_ARGS_COMMANDLINEPARSER_H_ */
