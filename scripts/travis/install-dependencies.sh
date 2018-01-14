#!/usr/bin/env bash
# (this script must be run as root)

apt-get update -qq
apt-get install -qq --no-install-recommends \
    build-essential \
    cmake \
    qtbase5-dev \
    libhdf5-dev \
    ocl-icd-opencl-dev \
    libprotobuf-dev \
    protobuf-compiler \
    libgrpc-dev \
    libgrpc++-dev \
    protobuf-compiler-grpc
