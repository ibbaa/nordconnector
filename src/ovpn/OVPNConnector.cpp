#include "ovpn/OVPNConnector.h"
#include "util/Output.h"
#include <stdlib.h>

int OVPNConnector::connect(const std::string &config, const std::string &credentials, bool daemon, const std::string &passthrough, bool verbose) {
    std::string ovpncmd = "openvpn --config " + config + " --auth-user-pass " + credentials;
    if (daemon) {
        ovpncmd += " --daemon";
    }
    if (!passthrough.empty()) {
        ovpncmd += " " + passthrough;
    }
    Output::output(ovpncmd + "\n", verbose);
    int ovpnresult = system(ovpncmd.c_str());
    Output::output("openvpn result code: " + std::to_string(ovpnresult) + "\n", verbose);
    return ovpnresult;
}

