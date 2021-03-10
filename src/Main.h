#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include "args/NVPNOptions.h"
#include <future>

class Main {
    public:
        int main(int argc, char *argv[]);
    private:
        void output(const NVPNOptions &options, const std::string &message);
        std::string get_from_future(std::future<std::string> &data);
        std::string select_server(const NVPNOptions &options);
};

#endif /* SRC_MAIN_H_ */
