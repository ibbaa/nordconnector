#ifndef SRC_OVPN_OVPNCONNECTOR_H_
#define SRC_OVPN_OVPNCONNECTOR_H_

#include <string>

class OVPNConnector {
    public:
        int connect(const std::string &config, const std::string &credentials, bool daemon, const std::string &passthrough, bool verbose);
};

#endif /* SRC_OVPN_OVPNCONNECTOR_H_ */
