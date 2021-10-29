#ifndef SRC_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_H_

#include <string>

class Server {
    private:
        std::string m_address;
        int m_load;
        bool m_provided;
    public:
        Server();
        Server(std::string address, int load, bool m_provided);
        std::string get_address() const;
        int get_load() const;
        bool is_provided() const;
};

#endif /* SRC_SERVER_SERVER_H_ */
