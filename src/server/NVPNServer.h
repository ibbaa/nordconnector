#ifndef SERVER_NVPNSERVER_H_
#define SERVER_NVPNSERVER_H_

#include <string>

class NVPNServer {
    private:
        std::string m_address;
        int m_loadfactor;
    public:
        NVPNServer(const std::string &address, int loadfactor);
        std::string get_address() const;
        int get_loadfactor() const;
        bool valid() const;
};

#endif /* SERVER_NVPNSERVER_H_ */
