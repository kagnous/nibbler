cmake_minimum_required(VERSION 3.16)
project(NibblerCheck)

include(FetchContent)

# Tente d'abord de trouver les libs installées
find_package(SFML 2 COMPONENTS graphics window system QUIET)
find_package(SDL2 QUIET)
find_package(Curses QUIET)

# Si NCURSES absent le télécharge
include(ExternalProject)

if(NOT CURSES_FOUND)
    message(STATUS "ncurses not found, downloading...")
    ExternalProject_Add(ncurses
        URL https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.4.tar.gz
        CONFIGURE_COMMAND ./configure --prefix=<INSTALL_DIR> --with-shared
        BUILD_COMMAND make
        INSTALL_COMMAND make install
        BUILD_IN_SOURCE 1
    )
endif()

# Si SFML absent → le télécharge et compile depuis les sources
if(NOT SFML_FOUND)
    message(STATUS "SFML not found, downloading...")
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif()

if(NOT SDL2_FOUND)
    message(STATUS "SDL2 not found, downloading...")
    FetchContent_Declare(SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.9)
    FetchContent_MakeAvailable(SDL2)
endif()