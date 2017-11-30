cmake_minimum_required(VERSION 3.5)
project(runtime-verification-system)

include_directories(${PROJECT_SOURCE_DIR}/src/DFA)
include_directories(${PROJECT_SOURCE_DIR}/src/tinyxml2)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

aux_source_directory(src/rvsDFA rvsDFA)
aux_source_directory(src/tinyxml2 tinyxml2)
aux_source_directory(src/DFA DFA)

set(src ${tinyxml2} ${DFA} src/rvsDFATestSelf.cpp )

add_executable(rvs ${src})

target_link_libraries(rvs z3)
