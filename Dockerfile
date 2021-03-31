FROM gcc:9.3

ARG UID
ARG GID

RUN groupadd -r -g $GID buildusr
RUN useradd -r -u $UID -g buildusr buildusr
RUN apt -y update
RUN apt -y install cmake python3-pip
RUN pip3 install conan
RUN conan profile new --detect default