cmake_minimum_required(VERSION 3.18)

project(
  blake-cpp
  VERSION 0.0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(Cache)
include(Sanitizers)
include(Warnings)

option(BUILD_TEST "Compile a test application" ON)

add_subdirectory(blake3-bindings)
add_subdirectory(lib)

if(BUILD_TEST)
  add_subdirectory(test)
endif()
