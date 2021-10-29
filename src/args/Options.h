#ifndef SRC_ARGS_OPTIONS_H_
#define SRC_ARGS_OPTIONS_H_

#include <string>
#include <vector>

class Options {
    private:
        bool m_server;
        bool m_daemon;
        std::vector<std::string> m_countries;
        std::string m_ovpn;
        std::string m_stat;
        std::string m_user;
        std::string m_password;
        std::string m_passthrough;
        int m_maxload;
        int m_loadtolerance;
        bool m_verbose;
        std::string m_message;
    public:
        Options(bool server, bool dameon, const std::vector<std::string> &countries, const std::string &ovpn, const std::string &stat, const std::string &user, const std::string &passsword,
                const std::string &passthrough, int loadtolerance, int maxload, bool verbose);
        bool get_server() const;
        bool get_daemon() const;
        std::vector<std::string> get_countries() const;
        std::string get_ovpn() const;
        std::string get_stat() const;
        std::string get_user() const;
        std::string get_password() const;
        std::string get_passthrough() const;
        int get_loadtolerance() const;
        int get_maxload() const;
        bool get_verbose() const;
        bool validate();
        std::string get_validation_message() const;
        std::string describe() const;
    private:
        std::string country_list() const;
        std::string invalid_country() const;
};

#endif /* SRC_ARGS_OPTIONS_H_ */
