#ifndef SERVER_SERVERLISTEXTRACTOR_H_
#define SERVER_SERVERLISTEXTRACTOR_H_

#include "server/Server.h"
#include <vector>
#include <string>
#include <random>
#include <iterator>
#include "Poco/JSON/Parser.h"

class ServerSelector {
    public:
        Server select(const std::string &data, const std::vector<std::string> &countries, int loadtolerance, int maxload, bool verbose);
    private:
        bool matching_country(const std::string &server, const std::string &country);
        bool valid(const std::string &server);
        int get_min_load(Poco::JSON::Object::Ptr json_servers, const std::string &country);
        std::vector<std::pair<std::string, int>> get_acc_servers(Poco::JSON::Object::Ptr json_servers, const std::string &country, int minload, int loadtolerance, int maxload);

        template<typename T>
        T select_random(T start, T end) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
            std::advance(start, dis(gen));
            return start;
        }
};

#endif /* SERVER_SERVERLISTEXTRACTOR_H_ */
