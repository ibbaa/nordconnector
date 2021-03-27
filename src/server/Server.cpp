#include <server/Server.h>

Server::Server() : m_address(""), m_load(-1) {
}

Server::Server(std::string address, int load) : m_address(address), m_load(load) {
}

std::string Server::get_address() const {
    return m_address;
}

int Server::get_load() const {
    return m_load;
}

