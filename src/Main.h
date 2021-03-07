#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include "args/NVPNOptions.h"

class Main {
    public:
        int main(int argc, char *argv[]);
    private:
        void output(const NVPNOptions &options, const std::string &message);
};

#endif /* SRC_MAIN_H_ */
