#ifndef SRC_ARGS_COMMANDLINEPARSER_H_
#define SRC_ARGS_COMMANDLINEPARSER_H_

#include "args/NVPNOptions.h"
#include <string>
#include <vector>
#include "cxxopts.hpp"

#define OVPN_URL_DEFAULT "https://downloads.nordcdn.com/configs/archives/servers/ovpn.zip"
#define STAT_URL_DEFAULT "https://api.nordvpn.com/server/stats"

class CommandLineParser {
    public:
        NVPNOptions parse(int argc, char *argv[]);
    private:
        bool get_server(const cxxopts::ParseResult &result) const;
        std::vector<std::string> get_countries(const cxxopts::ParseResult &result) const;
        std::string get_ovpn(const cxxopts::ParseResult &result) const;
        std::string get_stat(const cxxopts::ParseResult &result) const;
        std::string get_user(const cxxopts::ParseResult &result) const;
        std::string get_password(const cxxopts::ParseResult &result) const;
        bool get_verbose(const cxxopts::ParseResult &result) const;
};

#endif /* SRC_ARGS_COMMANDLINEPARSER_H_ */
