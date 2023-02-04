cmake_minimum_required(VERSION 3.24)
project(TIRank)

set(CMAKE_CXX_STANDARD 17)

add_executable(TIRank main.cpp Player.h Player.cpp)

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(main PRIVATE JsonCpp::JsonCpp)