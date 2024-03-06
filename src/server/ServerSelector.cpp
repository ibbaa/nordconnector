#include "server/ServerSelector.h"
#include "util/Output.h"
#include <stdlib.h>
#include <iostream>
#include "Poco/Foundation.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/JSON.h"
#include "Poco/JSON/Parser.h"

ServerSelector::ServerSelector() : m_cexpr("[a-z][a-z]\\d+") {
}

Server ServerSelector::select(const std::string &data, const std::vector<std::string> &countries, int loadtolerance, int maxload, bool verbose) {
    try {
        Poco::JSON::Parser json_parser;
        Poco::Dynamic::Var json_data = json_parser.parse(data);
        Poco::Dynamic::Var json_result = json_parser.result();
        Poco::JSON::Array::Ptr json_servers = json_result.extract<Poco::JSON::Array::Ptr>();
        std::string country;
        if (countries.empty()) {
            std::vector<std::string> all_countries;
            for (int ii = 0; ii < json_servers->size(); ii++) {
                Poco::JSON::Object::Ptr server = json_servers->getObject(ii);
                std::string hostname = server->getValue < std::string > ("hostname");
                if (valid(hostname)) {
                    all_countries.push_back(hostname.substr(0, 2));
                }
            }
            std::vector<std::string>::const_iterator country_iter = select_random(all_countries.begin(), all_countries.end());
            country = *country_iter;
        } else {
            std::vector<std::string>::const_iterator country_iter = select_random(countries.begin(), countries.end());
            country = *country_iter;
        }
        if (country.empty()) {
            Output::err_output("Unable to select suitable country\n");
            return Server { };
        }
        Output::output("Selected country: " + country + "\n", verbose);
        int min = get_min_load(json_servers, country);
        const std::vector<std::pair<std::string, int>> &servers = get_acc_servers(json_servers, country, min, loadtolerance, maxload);
        if (servers.empty()) {
            return Server { };
        }
        const std::pair<std::string, int> &server = *select_random(servers.begin(), servers.end());
        return Server { server.first, server.second, false };
    } catch (Poco::Exception &exc) {
        Output::err_output("Error parsing server data: " + exc.displayText() + "\n");
    } catch (...) {
        Output::err_output("Error parsing server data.\n");
    }
    return Server { };
}

int ServerSelector::get_min_load(const Poco::JSON::Array::Ptr &json_servers, const std::string &country) {
    int min = 100;
    for (int ii = 0; ii < json_servers->size(); ii++) {
        Poco::JSON::Object::Ptr server = json_servers->getObject(ii);
        std::string hostname = server->getValue < std::string > ("hostname");
        if (valid(hostname) && matching_country(hostname, country)) {
            int load = server->getValue<int>("load");
            if (load < min) {
                min = load;
            }
        }
    }
    return min;
}

std::vector<std::pair<std::string, int>> ServerSelector::get_acc_servers(const Poco::JSON::Array::Ptr &json_servers, const std::string &country, int minload, int loadtolerance, int maxload) {
    std::vector<std::pair<std::string, int>> servers;
    for (int ii = 0; ii < json_servers->size(); ii++) {
        Poco::JSON::Object::Ptr server = json_servers->getObject(ii);
        std::string hostname = server->getValue < std::string > ("hostname");
        if (valid(hostname) && matching_country(hostname, country)) {
            int load = server->getValue<int>("load");
            if (load <= minload) {
                servers.push_back(std::make_pair(hostname, load));
            } else if (load - minload <= loadtolerance && load <= maxload) {
                servers.push_back(std::make_pair(hostname, load));
            }
        }
    }
    return servers;
}

bool ServerSelector::matching_country(const std::string &hostname, const std::string &country) {
    return hostname.find(country) == 0;
}

bool ServerSelector::valid(const std::string &hostname) {
    int pos = hostname.rfind("nordvpn.com");
    if (pos != (hostname.length() - 11)) {
        return false;
    }
    int cpos = hostname.find(".");
    if (cpos == std::string::npos) {
        return false;
    }
    std::string cpart = hostname.substr(0, cpos);
    if (m_cexpr.match(cpart, 0, m_cmvec)) {
        return true;
    }
    return true;
}
