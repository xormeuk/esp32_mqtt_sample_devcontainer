# Use an official Python runtime as a parent image
FROM python:3.9-slim

# Set non-interactive installation mode for apt-get
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies required for PlatformIO and Mosquitto clients
RUN apt-get update && apt-get install -y --no-install-recommends \
    git \
    build-essential \
    mosquitto-clients \
    && rm -rf /var/lib/apt/lists/*

# Install PlatformIO
RUN pip install --no-cache-dir platformio

# Set the default shell to bash instead of sh
SHELL ["/bin/bash", "-c"]

# Create a non-root user to match VSCode's default behavior
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create the user with sudo privileges and no password requirement for sudo
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && rm -rf /var/lib/apt/lists/* # Clean up

USER $USERNAME

# Set the working directory in the container
WORKDIR /workspace

# Set the default command for the container
CMD ["bash"]
