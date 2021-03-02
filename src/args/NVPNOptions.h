#ifndef SRC_ARGS_NVPNOPTIONS_H_
#define SRC_ARGS_NVPNOPTIONS_H_

#include <string>
#include <vector>

class NVPNOptions {
    private:
        std::string m_server;
        std::vector<std::string> m_countries;
        std::string m_source;
        std::string m_user;
        std::string m_password;
    public:
        NVPNOptions(const std::string &m_server, const std::vector<std::string> &countries, const std::string &source, const std::string &user, const std::string &passsword);
        std::string get_server() const;
        std::vector<std::string> get_countries() const;
        std::string get_source() const;
        std::string get_user() const;
        std::string get_password() const;
};

#endif /* SRC_ARGS_NVPNOPTIONS_H_ */
