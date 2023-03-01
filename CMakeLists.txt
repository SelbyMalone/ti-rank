cmake_minimum_required(VERSION 3.24)
project(TIRank)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "C:/vcpkg/installed/x64-windows/share")

add_executable(TIRank main.cpp Player.h Player.cpp)

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(TIRank PRIVATE JsonCpp::JsonCpp)