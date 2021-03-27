#ifndef SRC_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_H_

#include <string>

class Server {
    private:
        std::string m_address;
        int m_load;
    public:
        Server();
        Server(std::string address, int load);
        std::string get_address() const;
        int get_load() const;
};

#endif /* SRC_SERVER_SERVER_H_ */
