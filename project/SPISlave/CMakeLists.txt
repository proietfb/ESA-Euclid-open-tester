project(SPISlave)
cmake_minimum_required(VERSION 2.6)
set( CMAKE_VERBOSE_MAKEFILE on )

include(${CMAKE_SOURCE_DIR}/scripts/arduino_mega.cmake)

add_subdirectory(src)
