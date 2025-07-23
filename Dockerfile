FROM debian:trixie

ARG UID
ARG GID

RUN groupadd -r -g $GID buildusr
RUN useradd -m -r -u $UID -g buildusr buildusr
RUN apt -y update
RUN apt -y install gcc g++ cmake libssl-dev libfindbin-libs-perl python3-venv
RUN python3 -m venv /opt/.conanenv
ENV PATH="/opt/.conanenv/bin:$PATH"
RUN python3 -m pip install conan
USER buildusr
