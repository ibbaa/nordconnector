#include "config/OVPNConfigReader.h"
#include "util/Output.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Poco/File.h"
#include "Poco/StreamCopier.h"
#include "Poco/Zip/Compress.h"
#include "Poco/Zip/ZipStream.h"

std::string OVPNConfigReader::extract_config(const std::string &config, const std::string &server, bool is_udp, bool verbose) {
    try {
        std::istringstream config_str(config);
        const Poco::Path &tmpdir_path = Output::create_tmp_dir();
        std::ofstream configf_str;
        std::string config_filename = get_config_file(tmpdir_path, server, is_udp);
        configf_str.open(config_filename, std::ios::out | std::ios::trunc);
        if (!configf_str.is_open()) {
            Output::err_output("Error opening file for openvpn configuration " + config_filename + "\n");
            return "";
        }
        Output::output("openvpn configuation file: " + config_filename + "\n", verbose);
        Poco::StreamCopier::copyStream(config_str, configf_str);
        close(configf_str, config_filename);
        return config_filename;
    } catch (...) {
        Output::err_output("Error writing openvpn configuration.\n");
    }
    return "";
}

std::string OVPNConfigReader::get_config_file(Poco::Path dir, const std::string &server, bool is_udp) {
    if (is_udp) {
        return dir.append(server + "." + OVPN_UDP_SUFFIX + "_" + Output::timestamp()).absolute().toString();
    }
    return dir.append(server + "." + OVPN_TCP_SUFFIX + "_" + Output::timestamp()).absolute().toString();
}

void OVPNConfigReader::close(std::ofstream &str, const std::string &filename) {
    try {
        if (str.is_open()) {
            str.flush();
            str.close();
        }
    } catch (...) {
        Output::err_output("Error closing file for openvpn configuration: " + filename + "\n");
    }
}
