#ifndef SRC_ARGS_NVPNOPTIONS_H_
#define SRC_ARGS_NVPNOPTIONS_H_

#include <string>
#include <vector>

class NVPNOptions {
    private:
        std::string m_server;
        std::vector<std::string> m_countries;
        std::string m_ovpn;
        std::string m_stat;
        std::string m_user;
        std::string m_password;
    public:
        NVPNOptions(const std::string &server, const std::vector<std::string> &countries, const std::string &ovpn, const std::string &stat, const std::string &user, const std::string &passsword);
        std::string get_server() const;
        std::vector<std::string> get_countries() const;
        std::string get_ovpn() const;
        std::string get_stat() const;
        std::string get_user() const;
        std::string get_password() const;
};

#endif /* SRC_ARGS_NVPNOPTIONS_H_ */
