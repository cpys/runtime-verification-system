cmake_minimum_required(VERSION 3.5)
project(runtime-verification-system)

include_directories(${PROJECT_SOURCE_DIR}/src/DFA)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

aux_source_directory(src/DFA DFA)

set(src ${DFA} src/DFATest.cpp)

add_executable(rvs ${src})

target_link_libraries(rvs z3)
