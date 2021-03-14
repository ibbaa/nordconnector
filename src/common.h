#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include <iostream>
#include <string>

#define DOWNLOAD_TIMEOUT 120

enum RETURN_CODES {
    OK = 0, GENERAL_ERROR = 1, PARSE_ERROR = 3, VALIDATION_ERROR = 4, SSL_INIT_ERROR = 5, DOWNLOAD_ERROR = 6, SELECT_ERROR = 7, TIMEOUT = 8, OVPN_CONFOG_ERROR = 9
};

class Commons {
    public:
        static void output(const std::string &message, bool verbose) {
            if (verbose) {
                std::cout << message;
            }
        }

        static void err_output(const std::string &message) {
            std::cerr << message;
        }
};

#endif /* SRC_COMMON_H_ */
