#include "common.h"
#include <server/ServerSelector.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <iterator>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

std::string ServerSelector::select(const std::string &data, const std::vector<std::string> &countries, bool verbose) {
    try {
        Poco::JSON::Parser jsonParser;
        Poco::Dynamic::Var jsonData = jsonParser.parse(data);
        Poco::Dynamic::Var jsonResult = jsonParser.result();
        Poco::JSON::Object::Ptr jsonServers = jsonResult.extract<Poco::JSON::Object::Ptr>();
        std::string country;
        if (countries.empty()) {
            std::vector<std::string> all_countries;
            for (Poco::JSON::Object::Iterator itr = jsonServers->begin(); itr != jsonServers->end(); ++itr) {
                std::string server = itr->first;
                if (valid(server)) {
                    all_countries.push_back(server.substr(0, 2));
                }
            }
            std::vector<std::string>::const_iterator country_iter = select_random(all_countries.begin(), all_countries.end());
            country = *country_iter;
        } else {
            std::vector<std::string>::const_iterator country_iter = select_random(countries.begin(), countries.end());
            country = *country_iter;
        }
        if (country.empty()) {
            std::cerr << "Unable to select suitable country\n";
            return "";
        }
        if (verbose) {
            std::cout << "Selected country: " << country << std::endl;
        }
        int min = 100;
        std::string sel_server;
        for (Poco::JSON::Object::Iterator itr = jsonServers->begin(); itr != jsonServers->end(); ++itr) {
            std::string server = itr->first;
            if (valid(server) && matching_country(server, country)) {
                Poco::JSON::Object::Ptr lf_obj = (itr->second).extract<Poco::JSON::Object::Ptr>();
                Poco::Dynamic::Var lf_obj_val = lf_obj->get("percent");
                if (lf_obj_val.isInteger()) {
                    int lf = lf_obj_val.convert<int>();
                    if (lf < min) {
                        min = lf;
                        sel_server = server;
                    }
                }
            }
        }
        return sel_server;
    } catch (Poco::Exception &exc) {
        std::cerr << "Error parsing server data: " << exc.displayText() << std::endl;
    }
    return "";
}

bool ServerSelector::matching_country(const std::string &server, const std::string &country) {
    return server.find(country) == 0;
}

bool ServerSelector::valid(const std::string &server) {
    int pos = server.rfind("nordvpn.com");
    if (pos != (server.length() - 11)) {
        return false;
    }
    int cpos = server.find(".");
    if (cpos == std::string::npos) {
        return false;
    }
    std::string cpart = server.substr(0, cpos);
    Poco::RegularExpression expr("[a-z][a-z]\\d+");
    Poco::RegularExpression::MatchVec mvec;
    if (expr.match(cpart, 0, mvec)) {
        return true;
    }
    return true;
}

std::vector<std::string>::const_iterator ServerSelector::select_random(std::vector<std::string>::const_iterator start, std::vector<std::string>::const_iterator end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(gen));
    return start;
}
