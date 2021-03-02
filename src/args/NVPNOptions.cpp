#include "args/NVPNOptions.h"

NVPNOptions::NVPNOptions(const std::string &m_server, const std::vector<std::string> &countries, const std::string &source, const std::string &user, const std::string &passsword) : m_server(m_server), m_countries(
        countries), m_source(source), m_user(user), m_password(passsword) {
}

std::string NVPNOptions::get_server() const {
    return m_server;
}

std::vector<std::string> NVPNOptions::get_countries() const {
    return m_countries;
}

std::string NVPNOptions::get_source() const {
    return m_source;
}

std::string NVPNOptions::get_user() const {
    return m_user;
}

std::string NVPNOptions::get_password() const {
    return m_password;
}
