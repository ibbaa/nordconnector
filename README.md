# nordconnector

An easy to use to use tool to connect to NordVPN services for Linux. It's a single C++ binary and does not require any additional setup except that OpenVPN must be installed. The feature set is very limited. The tool does not modify any network or system settings. This means it does not change DNS servers nor does it disable IPv6 for leakage prevention unless you set it manually or provide scripts for OpenVPN as described later on.

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

`nordc` will terminate immediately after starting `openvpn`. The `openvpn` process must be killed to drop the connection:

`killall --wait --verbose --signal SIGINT openvpn`

## Passthrough

`openvpn` is called with the command line options `--config`, `--auth-user-pass` and `--daemon` in daemon mode. `nordc` passes all options directly to `openvpn` specified with `-t` (or `--passthrough`):

`sudo nordc -v -u user -p password -t '--ping 5' de`

adds `--ping 5` to the `openvpn` call options.

This can be used to provide scripts for changing DNS settings when the connection goes up and down with the `openvpn` `--up` and `--down` options:

`sudo nordc -v -u user -p password -t '--script-security 2 --up ./myupscript.sh --down ./mydownscript.sh' de`

`--script-security 2` is necessary for `openvpn` to execute user scripts. No scripts are provided by the nordconnector project at the moment, however.

## Options

`nordc --help` prints all available options:

```
Alternative NordVPN connection tool
Usage:
  nordc [OPTION...] list of countries to connect (separated by blank), if -s is provided a specific server by name

  -s, --server           connect to a specific server by name, otherwise the
                         server is chosen based on a list of countries
  -d, --daemon           run openvpn in daemon mode
  -h, --help             Print help
  -o, --ovpn arg         Url to retrieve openvpn server configuration
                         (default:
                         https://downloads.nordcdn.com/configs/archives/servers/ovpn.zip)
  -a, --stat arg         Url to retrieve server statistics (default:
                         https://api.nordvpn.com/server/stats)
  -u, --user arg         User
  -p, --password arg     Password
  -t, --passthrough arg  command line options directly passed to openvpn
  -v, --verbose          Verbose output
```

