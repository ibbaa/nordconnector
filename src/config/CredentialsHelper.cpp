#include <config/CredentialsHelper.h>
#include "util/Output.h"
#include <fstream>
#include "Poco/Exception.h"

std::string CredentialsHelper::provide_ovpn_credentials(const std::string &server, const std::string &username, const std::string &password, bool verbose) {
    try {
        const Poco::Path &tmpdir_path = Output::create_tmp_dir();
        std::ofstream credf_str;
        std::string cred_filename = get_cred_file(tmpdir_path, server);
        credf_str.open(cred_filename, std::ios::out | std::ios::trunc);
        if (!credf_str.is_open()) {
            Output::err_output("Error opening file for openvpn credentials " + cred_filename + "\n");
            return "";
        }
        credf_str << username << std::endl << password << std::endl;
        close(credf_str, cred_filename);
        Output::output("openvpn credentials file: " + cred_filename + "\n", verbose);
        return cred_filename;
    } catch (Poco::Exception &exc) {
        Output::err_output("Error retrieving openvpn configuration: " + exc.displayText() + "\n");
    } catch (...) {
        Output::err_output("Error retrieving openvpn configuration.\n");
    }
    return "";
}

std::string CredentialsHelper::get_cred_file(Poco::Path dir, const std::string &server) {
    return dir.append(server + "." + CRED_FILE_NAME + "_" + Output::timestamp()).absolute().toString();
}

void CredentialsHelper::close(std::ofstream &str, const std::string &filename) {
    try {
        if (str.is_open()) {
            str.flush();
            str.close();
        }
    } catch (...) {
        Output::err_output("Error closing file for openvpn credentials: " + filename + "\n");
    }
}

