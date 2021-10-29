#ifndef SRC_CONFIG_CREDENTIALSHELPER_H_
#define SRC_CONFIG_CREDENTIALSHELPER_H_

#include <string>
#include "Poco/Path.h"

#define CRED_FILE_NAME "ovpn_credentials"

class CredentialsHelper {
    public:
        std::string provide_ovpn_credentials(const std::string &server, const std::string &username, const std::string &password, bool verbose);
    private:
        std::string get_cred_file(Poco::Path dir, const std::string &server);
        void close(std::ofstream &str, const std::string &filename);
};

#endif /* SRC_CONFIG_CREDENTIALSHELPER_H_ */
