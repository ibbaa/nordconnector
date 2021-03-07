#ifndef SERVER_SERVERLISTEXTRACTOR_H_
#define SERVER_SERVERLISTEXTRACTOR_H_

#include <server/NVPNServer.h>
#include <vector>

class ServerSelector {
    public:
        NVPNServer select(const std::string &data, bool server, const std::vector<std::string> &countries);
    private:
        bool valid(const std::string &data, const std::vector<std::string> &countries);
};

#endif /* SERVER_SERVERLISTEXTRACTOR_H_ */
