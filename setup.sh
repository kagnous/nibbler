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

make bonus
