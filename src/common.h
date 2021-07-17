#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include <iostream>
#include <string>

const std::string VERSION = "1.0.1";

const int DOWNLOAD_TIMEOUT = 120;

enum RETURN_CODES {
    OK = 0, GENERAL_ERROR = 1, PRIVILEGES_ERROR = 3, PARSE_ERROR = 4, VALIDATION_ERROR = 5, SSL_INIT_ERROR = 6, DOWNLOAD_ERROR = 7, SELECT_ERROR = 8, TIMEOUT = 9, OVPN_CONFIG_ERROR = 10
};

#endif /* SRC_COMMON_H_ */
