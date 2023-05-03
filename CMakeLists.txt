cmake_minimum_required(VERSION 3.23)
project(TIRank)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_executable(TIRank main.cpp Player.h Player.cpp)

set(jsoncpp_DIR "C:/vcpkg/installed/x64-windows/share/jsoncpp")
find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_lib)