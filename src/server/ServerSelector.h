#ifndef SERVER_SERVERLISTEXTRACTOR_H_
#define SERVER_SERVERLISTEXTRACTOR_H_

#include <vector>
#include <string>
#include "Poco/Foundation.h"
#include "Poco/RegularExpression.h"

class ServerSelector {
    public:
        std::string select(const std::string &data, const std::vector<std::string> &countries, bool verbose);
    private:
        bool matching_country(const std::string &server, const std::string &country);
        bool valid(const std::string &server);
        std::vector<std::string>::const_iterator select_random(std::vector<std::string>::const_iterator start, std::vector<std::string>::const_iterator end);
};

#endif /* SERVER_SERVERLISTEXTRACTOR_H_ */
