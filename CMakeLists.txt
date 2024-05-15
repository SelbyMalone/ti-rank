cmake_minimum_required(VERSION 3.24)
project(TIRank)

set(CMAKE_CXX_STANDARD 17)

add_executable(TIRank main.cpp Player.h Player.cpp)

# compiler flags for GCC/Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Set floating-point precision flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexcess-precision=standard -ffloat-store")
endif()

# compiler flags for MSVC
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # Enable floating-point consistency
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:precise")
endif()