# From https://blog.memzero.de/cmake-cargo-example/

cmake_minimum_required(VERSION 3.14)

set(blake3_build_dir ${CMAKE_BINARY_DIR}/blake3-bindings)
set(blake3_library_name "libblake3_bindings.a")

# Define external project to build rust lib with cargo.
include(ExternalProject)
ExternalProject_Add(
  ext_blake3
  # Always trigger build, let cargo decide if we want to rebuild.
  BUILD_ALWAYS ON
  CONFIGURE_COMMAND ""
  # Can not pass arguments to build.rs and was not able to set env variables for
  # the external build command, therefore use 'env' to setup env var.
  BUILD_COMMAND env BUILD_DIR=${blake3_build_dir} cargo build --target-dir
                ${blake3_build_dir} "$<IF:$<CONFIG:Release>,--release,>"
  BUILD_BYPRODUCTS
    ${blake3_build_dir}/$<IF:$<CONFIG:Release>,release,debug>/${blake3_library_name}
    ${blake3_build_dir}/blake3.h
  INSTALL_COMMAND ""
  # Location of sources (since we don't download).
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  # Build dir location used as CWD for build commands.
  BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  # Root directory for external project in cmake build dir.
  PREFIX "blake3"
  # Log directory (relative to PREFIX).
  LOG_DIR "log"
  # Log build step.
  LOG_BUILD ON
  # In case of error output log on terminal.
  LOG_OUTPUT_ON_FAILURE ON)

# Define pseudo target (import lib) for usage in cmake and let it depend on the
# cargo build.
add_library(blake3 STATIC IMPORTED GLOBAL)
add_dependencies(blake3 ext_blake3)

# Configure the import locations (libs) for the import lib.
set_target_properties(
  blake3
  PROPERTIES IMPORTED_CONFIGURATIONS "Debug;Release"
             IMPORTED_LOCATION
             "${blake3_build_dir}/release/${blake3_library_name}"
             IMPORTED_LOCATION_DEBUG
             "${blake3_build_dir}/debug/${blake3_library_name}")

# Configure the additional interface for they pseudo target.
target_include_directories(blake3 INTERFACE "${blake3_build_dir}")
