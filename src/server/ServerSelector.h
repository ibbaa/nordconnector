#ifndef SERVER_SERVERLISTEXTRACTOR_H_
#define SERVER_SERVERLISTEXTRACTOR_H_

#include <server/NVPNServer.h>
#include <vector>

class ServerSelector {
    public:
        NVPNServer select(const std::string &data, const std::vector<std::string> &countries);
    private:
        bool valid(const std::string &data, const std::vector<std::string> &countries);
        std::vector<std::string>::const_iterator select_random(std::vector<std::string>::const_iterator start, std::vector<std::string>::const_iterator end);
};

#endif /* SERVER_SERVERLISTEXTRACTOR_H_ */
