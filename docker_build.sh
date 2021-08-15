#!/bin/sh
UID=$(id -u)
GID=$(id -g)
docker build --no-cache --build-arg UID=$UID --build-arg GID=$GID -t ibbaa/nordc:build .
docker run --rm -v $PWD:/var/nordc -w /var/nordc ibbaa/nordc:build /bin/bash -c "./build.sh dockerbuild"
RET=$?
docker image prune -f
exit $RET