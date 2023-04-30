FROM debian:bullseye

ARG UID
ARG GID

RUN groupadd -r -g $GID buildusr
RUN useradd -m -r -u $UID -g buildusr buildusr
RUN apt -y update
RUN apt -y install cmake python3-pip
RUN pip3 install conan
USER buildusr
