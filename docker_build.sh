#!/bin/sh
UID=$(id -u)
GID=$(id -g)
docker build --no-cache --build-arg UID=$UID --build-arg GID=$GID -t ibbaa/nordc:1.0 .
docker run --rm -v $PWD:/var/nordc -w /var/nordc ibbaa/nordc:1.0 /bin/bash -c "./build.sh dockerbuild && chown -R buildusr:buildusr dockerbuild"
docker image prune -f