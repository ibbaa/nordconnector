#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include <iostream>
#include <string>

const int DOWNLOAD_TIMEOUT = 120;

enum RETURN_CODES {
    OK = 0, GENERAL_ERROR = 1, PARSE_ERROR = 3, VALIDATION_ERROR = 4, SSL_INIT_ERROR = 5, DOWNLOAD_ERROR = 6, SELECT_ERROR = 7, TIMEOUT = 8, OVPN_CONFIG_ERROR = 9
};

#endif /* SRC_COMMON_H_ */
