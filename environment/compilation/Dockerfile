FROM nvidia/vulkan:1.1.121

RUN export DEBIAN_FRONTEND=noninteractive  \
    && apt-get update \
    && apt-get upgrade -y \
    && apt install -y \
        wget \
        gnupg2 \
        lsb-release \
        apt-utils \
        software-properties-common \
        cmake \
        make \
        git \
        build-essential \
        manpages-dev \
        tar \
        curl \
        zip \
        unzip \
        libxinerama-dev \
        libxcursor-dev \
        xorg-dev \
        libglu1-mesa-dev \
    && add-apt-repository ppa:ubuntu-toolchain-r/test \
    && wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null \
    && apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main' \
    && readonly DEBIAN_PACKAGES="g++-10" \
    && readonly CLANG_PACKAGES="11" \
    && apt-get update \
    && apt-get upgrade -y \
    && apt install -y \
        g++-10 \
    && wget https://apt.llvm.org/llvm.sh \
    && chmod +x llvm.sh \
    && ./llvm.sh 11 \
    && git clone https://github.com/microsoft/vcpkg \
    && ./vcpkg/bootstrap-vcpkg.sh \
    && apt autoremove --purge -y \
    && apt autoclean -y \
    && rm -rf /var/cache/apt/*

RUN ./vcpkg/vcpkg install \
    glm \
    fmt \
    spdlog \
    gtest \
    glfw3

ARG CC=gcc
ARG CXX=g++

WORKDIR /usr/ostl/out
VOLUME [ "/usr/ostl" ]

COPY . /usr/ostl/

ENV cc=${CC}
ENV cxx=${CXX}

ENTRYPOINT ["/bin/sh", "-c"]
# CMD ["ctest", "--verbose"]
CMD ["cmake \
        -G \"Unix Makefiles\" \
        -DCMAKE_C_COMPILER=${cc} \
        -DCMAKE_CXX_COMPILER=${cxx} \
        -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake \
        .. \
    && make all VERBOSE=1 \
    && ./source/ostl/ostl"]
