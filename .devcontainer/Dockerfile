# Use an official Python runtime as a parent image
FROM python:3.9-slim

# Install system dependencies
RUN apt-get update && apt-get install -y --no-install-recommends     git     build-essential     && rm -rf /var/lib/apt/lists/*

# Install PlatformIO
RUN pip install --no-cache-dir platformio

# Set the default shell to bash instead of sh
SHELL ["/bin/bash", "-c"]

# Create a non-root user
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create the user
RUN groupadd --gid $USER_GID $USERNAME     && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME     && apt-get update     && apt-get install -y sudo     && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME     && chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME

# Set the working directory
WORKDIR /workspace

# Set the default command for the container
CMD ["bash"]
