#!/bin/bash

set -e

cmake -B build_check -DCMAKE_INSTALL_PREFIX="$PWD/build_check/install"

if [ -d "build_check/ncurses-prefix" ]; then
    echo "Building downloaded ncurses..."
    cmake --build build_check --target ncurses
    export PKG_CONFIG_PATH="$PWD/build_check/ncurses-prefix/lib/pkgconfig:$PKG_CONFIG_PATH"
    export LD_LIBRARY_PATH="$PWD/build_check/ncurses-prefix/lib:$LD_LIBRARY_PATH"
    export CPLUS_INCLUDE_PATH="$PWD/build_check/ncurses-prefix/include/ncurses:$CPLUS_INCLUDE_PATH"
fi

if [ -d "build_check/_deps/sfml-src" ]; then
    echo "Building downloaded SFML..."
    cmake --build build_check
    cmake --install build_check
    export PKG_CONFIG_PATH="$PWD/build_check/install/pkgconfig:$PKG_CONFIG_PATH"
    export LD_LIBRARY_PATH="$PWD/build_check/install/lib:$LD_LIBRARY_PATH"
    export CPLUS_INCLUDE_PATH="$PWD/build_check/install/include:$CPLUS_INCLUDE_PATH"
fi

if [ -d "build_check/_deps/sdl2-src" ]; then
    echo "Building downloaded SDL2..."
    cmake --build build_check --target SDL2
    cmake --install build_check --prefix build_check/install
    export PKG_CONFIG_PATH="$PWD/build_check/install/lib/pkgconfig:$PKG_CONFIG_PATH"
    export LD_LIBRARY_PATH="$PWD/build_check/install/lib:$LD_LIBRARY_PATH"
fi

# Determine build target
TARGET="$1"
if [ -z "$TARGET" ]; then
    echo ""
    echo "What do you want to build?"
    echo "  [1] base"
    echo "  [2] bonus"
    read -rp "Choice (1/2): " choice
    case "$choice" in
        1) TARGET="base" ;;
        2) TARGET="bonus" ;;
        *) echo "Invalid choice, defaulting to base"; TARGET="base" ;;
    esac
fi

case "$TARGET" in
    base)  make ;;
    bonus) make bonus ;;
    *)     echo "Unknown target '$TARGET'. Use 'base' or 'bonus'."; exit 1 ;;
esac