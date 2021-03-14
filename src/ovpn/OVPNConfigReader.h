#ifndef SRC_OVPN_OVPNCONFIGREADER_H_
#define SRC_OVPN_OVPNCONFIGREADER_H_

#include <string>

#define OVPN_UDP_ZIP_FOLDER "ovpn_udp"
#define OVPN_TCP_ZIP_FOLDER "ovpn_tcp"
#define OVPN_UDP_SUFFIX "udp.ovpn"
#define OVPN_TCP_SUFFIX "tcp.ovpn"
#define NORDVPNCC_DIR "nordvpncc"

class OVPNConfigReader {
    public:
        std::string extract_config(const std::string &config, const std::string &server, const std::string &dir, bool verbose);
    private:
        std::string create_tmp_dir(const std::string &dir);
        std::string get_config_file(const std::string &dir, const std::string &server, bool is_udp);
        void close(std::ofstream &str, const std::string &filename);
};

#endif /* SRC_OVPN_OVPNCONFIGREADER_H_ */
