#include "common.h"
#include <server/ServerSelector.h>
#include <stdlib.h>
#include <iostream>
#include  <random>
#include  <iterator>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

NVPNServer ServerSelector::select(const std::string &data, const std::vector<std::string> &countries) {
    try {
        std::string country = *select_random(countries.begin(), countries.end());
        std::cout << data << std::endl;
        Poco::JSON::Parser jsonParser;
        Poco::Dynamic::Var jsonData = jsonParser.parse(data);
        Poco::Dynamic::Var jsonResult = jsonParser.result();
        Poco::JSON::Object::Ptr jsonServers = jsonResult.extract<Poco::JSON::Object::Ptr>();
        for (Poco::JSON::Object::Iterator itr = jsonServers->begin(); itr != jsonServers->end(); ++itr) {
            std::string name = itr->first;
            std::cout << name << std::endl;
        }

    } catch (Poco::Exception &exc) {
        std::cerr << "Error parsing server data: " << exc.displayText() << std::endl;
    }
    return NVPNServer("", 0);
}

bool ServerSelector::valid(const std::string &data, const std::vector<std::string> &countries) {
    return false;
}

std::vector<std::string>::const_iterator ServerSelector::select_random(std::vector<std::string>::const_iterator start, std::vector<std::string>::const_iterator end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(gen));
    return start;
}
