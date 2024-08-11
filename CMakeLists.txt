cmake_minimum_required(VERSION 3.23.2)
project(TIRank)

set(CMAKE_CXX_STANDARD 17)

#Define source files
set(SOURCES main.cpp Player.h Player.cpp)

#Windows
add_custom_target (TI-Rank_windows ALL
  COMMAND "x86_64-w64-mingw32-g++" -o ${CMAKE_BINARY_DIR}/out/TI-Rank.exe ${SOURCES}
)

#Linux
add_executable(TI-Rank ${SOURCES})
set_target_properties(TI-Rank PROPERTIES
  OUTPUT_NAME "TI-Rank"
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/
)
