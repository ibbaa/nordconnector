#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include "args/NVPNOptions.h"
#include "server/NVPNServer.h"

class Main {
    public:
        int main(int argc, char *argv[]);
    private:
        void output(const NVPNOptions &options, const std::string &message);
        NVPNServer select_server(const NVPNOptions &options);
};

#endif /* SRC_MAIN_H_ */
