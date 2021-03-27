#include "args/NVPNOptions.h"
#include <iostream>

NVPNOptions::NVPNOptions(bool server, bool daemon, const std::vector<std::string> &countries, const std::string &ovpn, const std::string &stat, const std::string &user, const std::string &passsword,
        const std::string &passthrough, int loadtolerance, int maxload, bool verbose) : m_server(server), m_daemon(daemon), m_countries(countries), m_ovpn(ovpn), m_stat(stat), m_user(user), m_password(
        passsword), m_passthrough(passthrough), m_loadtolerance(loadtolerance), m_maxload(maxload), m_verbose(verbose), m_message("") {
}

bool NVPNOptions::get_server() const {
    return m_server;
}

bool NVPNOptions::get_daemon() const {
    return m_daemon;
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

std::string NVPNOptions::get_passthrough() const {
    return m_passthrough;
}

int NVPNOptions::get_loadtolerance() const {
    return m_loadtolerance;
}

int NVPNOptions::get_maxload() const {
    return m_maxload;
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
    if (m_user.empty() || m_password.empty()) {
        valid = false;
        m_message += "-u,--user and -p,--password must be provided\n";
    }
    if (m_server && m_countries.empty()) {
        valid = false;
        m_message += "With -s,--server a server name must be provided\n";
    }
    if (m_ovpn.empty()) {
        valid = false;
        m_message += "-o,--ovpn arg must not be empty, if provided\n";
    }
    if (m_stat.empty()) {
        valid = false;
        m_message += "-a,--stat arg must not be empty, if provided\n";
    }
    if (m_loadtolerance < 0 || m_loadtolerance > 100) {
        valid = false;
        m_message += "-l,--loadtolerance min value: 0 max value: 100\n";
    }
    if (m_maxload < 0 || m_maxload > 100) {
        valid = false;
        m_message += "-m,--maxload min value: 0 max value: 100\n";
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
    desc += "Password: " + std::string(m_password.size() > 0 ? "*********" : "not provided") + "\n";
    desc += "Daemon: " + std::string(m_daemon ? "true" : "false") + "\n";
    desc += "Passthrough: " + std::string(m_passthrough.size() > 0 ? m_passthrough : "not provided") + "\n";
    desc += "Load tolerance: " + std::to_string(m_loadtolerance) + "\n";
    desc += "Max load: " + std::to_string(m_maxload) + "\n";
    return desc;
}

std::string NVPNOptions::country_list() const {
    std::string desc;
    for (std::vector<int>::size_type ii = 0; ii != m_countries.size(); ii++) {
        desc += m_countries[ii] + " ";
    }
    return desc;
}
