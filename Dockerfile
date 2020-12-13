# Start from clean ubuntu
FROM ubuntu:20.04

# Update registry
# RUN apt-get update

RUN apt-get update

# Install all necessary tools
RUN apt-get install -y gcc-8 g++-8 unzip  wget git make

# Install all RadioStream dependencies
Run apt-get install -y libx11-dev libfreetype6 libfreetype6-dev libxft-dev libxcursor-dev libssl-dev

# Install cmake
RUN wget -qO- "https://cmake.org/files/v3.16/cmake-3.16.9-Linux-x86_64.tar.gz" | \
  tar --strip-components=1 -xz -C /usr/local

# Point gcc and g++ to the correct version
RUN ln -s /usr/bin/gcc-8 /usr/local/bin/gcc
RUN ln -s /usr/bin/g++-8 /usr/local/bin/g++
