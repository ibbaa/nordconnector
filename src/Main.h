#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <args/Options.h>
#include "server/Server.h"
#include <future>

class Main {
    public:
        int main(int argc, char *argv[]);
    private:
        bool is_root();
        std::string get_from_future(std::future<std::string> &data);
        std::string download_servers(const Options &options);
        Server select_provided_server(const Options &options);
        Server select_server(const std::string stat_data, const Options &options);
        void log_sever(const Server &server, const Options &options);
};

#endif /* SRC_MAIN_H_ */
