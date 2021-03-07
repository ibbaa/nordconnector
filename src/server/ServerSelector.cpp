#include "common.h"
#include <server/ServerSelector.h>
#include <stdlib.h>
#include <iostream>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

NVPNServer ServerSelector::select(const std::string &data, bool server, const std::vector<std::string> &countries) {
    if (server) {
        if (countries.size() <= 0) {
            std::cerr << "-s/--server provided but no server specified\n";
            exit(RETURN_CODES::GENERAL_ERROR);
        }
        return NVPNServer(countries[0], 0);
    }
    Poco::JSON::Parser jsonParser;
    Poco::Dynamic::Var jsonData = jsonParser.parse(data);
    Poco::Dynamic::Var jsonResult = jsonParser.result();
    return NVPNServer("", 0);
}

bool ServerSelector::valid(const std::string &data, const std::vector<std::string> &countries) {

    return false;
}

