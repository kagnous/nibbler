#!/bin/bash

set -e

echo "Installing Nibbler dependencies..."

# Détecte le gestionnaire de paquets
if command -v apt-get &> /dev/null; then
    sudo apt-get update || true
    sudo apt-get install -y \
        libsfml-dev \
        libsdl2-dev \
        libncursesw5-dev \
        pkg-config \
        build-essential
elif command -v dnf &> /dev/null; then
    sudo dnf install -y \
        SFML-devel \
        SDL2-devel \
        ncurses-devel \
        pkg-config \
        gcc-c++ make
elif command -v pacman &> /dev/null; then
    sudo pacman -Sy --noconfirm \
        sfml \
        sdl2 \
        ncurses \
        pkgconf \
        base-devel
else
    echo "ERROR: No supported package manager found (apt, dnf, pacman)"
    exit 1
fi

echo "All dependencies installed."
echo "Run 'make' to build Nibbler, or 'make bonus' for the bonus version."