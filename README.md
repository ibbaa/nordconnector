# nordconnector

An easy to use to use tool to connect to NordVPN services for Linux. It's a single C++ binary and does not require any additional setup except that OpenVPN must be installed. The feature set is very limited. The tool does not modify any network or system settings. This means it does not change DNS servers nor does it disable IPv6 for leakage prevention unless you set it manually or provide scripts for OpenVPN. 

NordVPN configuration files are downloaded and kept in memory. The OpenVPN configuration file for the selected server and the credentials file are written to `/tmp/nordc` and are deleted when the `nordc` process terminates.

## Usage

Copy the binary file anywhere you want, e.g. `/usr/local/bin`. The tool does require sudo privileges. At least your NordVPN username and password must be provided:

`sudo nordc -v -u user -p password`

randomly chooses a country and connects to the server with the least load. It will take a few seconds because the configuration files are downloaded. `-v` gives verbose output and may be ommitted.

It is probably better to provide a country to connect:

`sudo nordc -v -u user -p password de`

connects to the least busy server in germany.

`sudo nordc -v -u user -p password de it`

randomly chooses one country, germany or italy, and connects to the least busy server there.

The option `-s` lets you provide a specific server to connect:

`sudo nordc -v -s -u user -p password de961.nordvpn.com`

## Daemon mode

Normally `nordc` starts `openvpn` and waits for its termination in the foreground. You can drop the connection by typing `CTRL + C` in the console or by killing either the `nordc` or `openvpn` process. It's possible to start `openvpn` in daemon mode with `-d`:

`sudo nordc -v -d -u user -p password de`

`nordc` will terminate immediately iafter starting `openvpn`. The `openvpn` process must be killed to drop the connection:

`killall --wait --verbose --signal SIGINT openvpn`

## Passthrough

`openvpn` is called with the command line options `--config`, `--auth-user-pass` and `--daemon` in daemon mode. `nordc` passes all options directly to `openvpn` specified with `-t` (or `--passthrough`):
