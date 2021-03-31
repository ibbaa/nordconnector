FROM gcc:9.3

ARG UID
ARG GID

RUN groupadd -r buildusr -g $GID
RUN useradd -u $UID -r -g buildusr buildusr
RUN apt -y update
RUN apt -y install cmake python3-pip
RUN pip3 install conan
RUN conan profile new --detect default