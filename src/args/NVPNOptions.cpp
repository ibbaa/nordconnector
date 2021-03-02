#include "args/NVPNOptions.h"

NVPNOptions::NVPNOptions(const std::string &server, const std::vector<std::string> &countries, const std::string &ovpn, const std::string &stat, const std::string &user, const std::string &passsword) : m_server(
        server), m_countries(countries), m_ovpn(ovpn), m_stat(stat), m_user(user), m_password(passsword) {
}

std::string NVPNOptions::get_server() const {
    return m_server;
}

std::vector<std::string> NVPNOptions::get_countries() const {
    return m_countries;
}

std::string NVPNOptions::get_ovpn() const {
    return m_ovpn;
}

std::string NVPNOptions::get_stat() const {
    return m_stat;
}

std::string NVPNOptions::get_user() const {
    return m_user;
}

std::string NVPNOptions::get_password() const {
    return m_password;
}
