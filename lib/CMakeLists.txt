set(LIB_NAME blake3-cpp)

add_library(blake3-cpp src/Hash.cpp)
target_include_directories(${LIB_NAME} PUBLIC include)
target_precompile_headers(${LIB_NAME} PUBLIC "include/Precompiled.hpp")

target_link_libraries(${LIB_NAME} PUBLIC blake3)

enable_sanitizers(${LIB_NAME})
set_project_warnings(${LIB_NAME})
