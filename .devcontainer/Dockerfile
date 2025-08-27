FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Install system packages, MPI, build tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    mpich \
    git \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /workspace
