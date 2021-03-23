# nordvpncc

An easy to use to use tool to connect to NordVPN services for Linux. It's a single C++ binary and does not require any additional setup except that OpenVPN must be installed. The feature set is very limited. The tool does not modify any network or system settings. This means it does not change DNS servers nor does it disable IPv6 for leakage prevention unless you set it manually or provide scripts for OpenVPN. NordVPN configuration files are downloaded and kept in memory. The OpenVPN configuration file for the selected server and the credentials file are written to `/tmp/nordvpncc` and are deleted when the connection drops.

## Usage

Copy the binary file anywhere you want, e.g. `/usr/local/bin`. The tool does require sudo privileges. At least your NordVPN username and password must be provided:

`sudo nordvpncc -v -u user -p password`

randomly chooses a country and connects to the server with the least load. It will take a few seconds because the configuration files are downloaded. `-v` gives verbose output and may be ommitted.

It is probably better to provide a country to connect:

`sudo nordvpncc -v -u user -p password de`

connects to the least busy server in germany.

`sudo nordvpncc -v -u user -p password de it`

randomly chooses one country, germany or italy, and connects to the least busy server there.

The option `-s` lets you provide a specific server to connect:

`sudo nordvpncc -v -s -u user -p password de961.nordvpn.com`
