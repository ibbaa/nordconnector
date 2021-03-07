#include <server/NVPNServer.h>

NVPNServer::NVPNServer(const std::string &address, int loadfactor) : m_address(address), m_loadfactor(loadfactor) {
}

std::string NVPNServer::get_address() const {
    return m_address;
}

int NVPNServer::get_loadfactor() const {
    return m_loadfactor;
}

bool NVPNServer::valid() const {
    return m_loadfactor >= 0;
}
