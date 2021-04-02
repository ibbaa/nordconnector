# nordconnector

An easy to use tool to connect to NordVPN services for Linux. It's a single C++ binary and does not require any additional setup except that OpenVPN must be installed. The feature set is very limited. The tool does not modify any network or system settings. This means it does not change DNS servers nor does it disable IPv6 for leakage prevention unless you set it manually or provide scripts for OpenVPN as described later on.

NordVPN configuration files are downloaded and kept in memory. The OpenVPN configuration file for the selected server and the credentials file are written to `/tmp/nordc` and are deleted when the `nordc` process terminates.

## Usage

Copy the binary file anywhere you want, e.g. `/usr/local/bin`. The tool does require sudo privileges. At least your NordVPN username and password must be provided:

`sudo nordc -v -u user -p password`

randomly chooses a country and connects to a server meeting the load requirements. It will take a few seconds because the configuration files are downloaded. `-v` gives verbose output and may be ommitted.

It is probably better to provide a country to connect:

`sudo nordc -v -u user -p password de`

connects to a server in Germany meeting the load requirements.

`sudo nordc -v -u user -p password de it`

randomly chooses one country, Germany or Italy, and connects to a server there that meets the load requirements.

The option `-s` lets you provide a specific server to connect:

`sudo nordc -v -s -u user -p password de961.nordvpn.com`

## Load requirements

`nordc` finds the least busy servers, i.e. the servers with the minimum load factor value while respecting a tolerance specified by the `--loadtolerance` option (0 to 100, default is 5). E.g., if the minimum load factor is 20 and the tolerance is 5, a server with a load factor of 24 is acceptable and will be taken into account. From the list of servers meeting these requirements, one will be chosen randomly. It's possible to provide a maximum acceptable load factor with the `--maxload` option (0 to 100, default is 70). Servers with a load factor above the maximum will be ignored. If no servers with a load factor below the maximum are available, the least busy server is selected. The tolerance value is ignored in this case.

## Daemon mode

Normally `nordc` starts `openvpn` and waits for its termination in the foreground. You can drop the connection by typing `CTRL + C` in the console or by killing either the `nordc` or `openvpn` process. It's possible to start `openvpn` in daemon mode with `-d`:

`sudo nordc -v -d -u user -p password de`

`nordc` will terminate immediately after starting `openvpn`. The `openvpn` process must be killed to drop the connection:

`killall --wait --verbose --signal SIGINT openvpn`

## Passthrough

`openvpn` is called with the command line options `--config`, `--auth-user-pass` and `--daemon` in daemon mode. `nordc` passes all options directly to `openvpn` specified with `-t` (or `--passthrough`):

`sudo nordc -v -u user -p password -t '--ping 5' de`

adds `--ping 5` to the `openvpn` call options.

This can be used to provide scripts for changing DNS settings when the connection is established and terminated with the `openvpn` `--up` and `--down` options:

`sudo nordc -v -u user -p password -t '--script-security 2 --up ./myupscript.sh --down ./mydownscript.sh' de`

`--script-security 2` is necessary for `openvpn` to execute user scripts. No scripts are provided by the nordconnector project at the moment, however.

## Build

The released binary is compiled and statically linked for 64Bit x86 architecture and should run under most modern Linux distributions. If not, you can try to build it yourself. `nordc` is written in C++ 11 and uses CMake and Conan (https://conan.io/). Two build variants are available: Locally and in a docker container.

### Local

For the local build, CMake and Conan must be installed. Simply call `./build.sh` in the main branch. The release binary is located under `build/Release/bin`. The script `sharedbuild/build.sh` builds a dynamically linked variant with shared libraries. The shared library version will be located under `sharedbuild/build/Release/bin`, the shared libraries are located under `sharedbuild/build/Release/lib`. There is a wrapper script `nordc.sh` which sets the `LD_LIBRARY_PATH` according to this package structure `bin` and `lib` in a directory. Alternatively you can copy the necessary libraries to a shared library default location of your system. It is recommended to use the statically linked version without the shared library hassle.

### Docker

There are no installation prerequisites for the docker build (except for docker, of course). `./docker_build.sh` creates the docker image and triggers the build. The project directory is mounted in the container. The release binary is located under `dockerbuild/Release/bin`. The docker build installs everything from scratch and takes much longer but provides a clean and reproducible build environment. The docker build creates the statically linked variant but it should be possible to build the dynamically linked variant with the same docker file.

### 

## Options

`nordc --help` prints all available options:

```
nordc version 1.0.0, build time Apr  2 2021 08:35:16
Usage:
  ./nordc [OPTION...] list of countries to connect (separated by blank), if -s is provided a specific server by name

  -s, --server             connect to a specific server by name, otherwise
                           the server is chosen based on a list of countries
  -d, --daemon             run openvpn in daemon mode
  -h, --help               Print help
  -o, --ovpn arg           Url to retrieve openvpn server configuration
                           (default:
                           https://downloads.nordcdn.com/configs/archives/servers/ovpn.zip)
  -a, --stat arg           Url to retrieve server statistics (default:
                           https://api.nordvpn.com/server/stats)
  -u, --user arg           User
  -p, --password arg       Password
  -t, --passthrough arg    command line options directly passed to openvpn
  -l, --loadtolerance arg  acceptable load tolerance (0 to 100) (default: 5)
  -m, --maxload arg        maximum acceptable load (0 to 100) (default: 70)
  -v, --verbose            Verbose output

```

