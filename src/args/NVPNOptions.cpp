#include "args/NVPNOptions.h"
#include <iostream>

NVPNOptions::NVPNOptions(bool server, const std::vector<std::string> &countries, const std::string &ovpn, const std::string &stat, const std::string &user, const std::string &passsword, bool verbose) : m_server(
        server), m_countries(countries), m_ovpn(ovpn), m_stat(stat), m_user(user), m_password(passsword), m_verbose(verbose), m_message("") {
}

bool NVPNOptions::get_server() const {
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

std::string NVPNOptions::get_validation_message() const {
    return m_message;
}

bool NVPNOptions::get_verbose() const {
    return m_verbose;
}

bool NVPNOptions::validate() {
    m_message = "";
    bool valid = true;
    if (m_server && m_countries.empty()) {
        valid = false;
        m_message += "With -s/--server a server name must be provided.\n";
    }
    if (m_ovpn.empty()) {
        valid = false;
        m_message += "-o,--ovpn arg must not be empty, if provided.\n";
    }
    if (m_stat.empty()) {
        valid = false;
        m_message += "-a,--stat arg must not be empty, if provided.\n";
    }
    return valid;
}

std::string NVPNOptions::describe() const {
    std::string desc;
    if (m_server) {
        desc += "Server: " + (m_countries.size() > 0 ? m_countries[0] : "not provided") + "\n";
    } else {
        std::string clistdesc = country_list();
        desc += "Countries: " + (clistdesc.size() > 0 ? clistdesc : "none provided") + "\n";
    }
    desc += "OpenVPN configuration url: " + (m_ovpn.size() > 0 ? m_ovpn : "not provided") + "\n";
    desc += "Server statistics url: " + (m_stat.size() > 0 ? m_stat : "not provided") + "\n";
    desc += "User: " + (m_user.size() > 0 ? m_user : "not provided") + "\n";
    desc += "Password: " + std::string((m_password.size() > 0 ? "*********" : "not provided")) + "\n";
    return desc;
}

std::string NVPNOptions::country_list() const {
    std::string desc;
    for (std::vector<int>::size_type ii = 0; ii != m_countries.size(); ii++) {
        desc += m_countries[ii] + " ";
    }
    return desc;
}
