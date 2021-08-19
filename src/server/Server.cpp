#include <server/Server.h>

Server::Server() : m_address(""), m_load(-1), m_provided(false) {
}

Server::Server(std::string address, int load, bool provided) : m_address(address), m_load(load), m_provided(provided) {
}

std::string Server::get_address() const {
    return m_address;
}

int Server::get_load() const {
    return m_load;
}

bool Server::is_provided() const {
    return m_provided;
}

