cmake_minimum_required(VERSION 3.6)
project(runtime-verification-system)

include_directories(${PROJECT_SOURCE_DIR}/src/rvsDFAInterface)
include_directories(${PROJECT_SOURCE_DIR}/src/rvsDFA/headers)
include_directories(${PROJECT_SOURCE_DIR}/src/tinyxml2)
include_directories(${PROJECT_SOURCE_DIR}/src/serialForward)
#include_directories(${PROJECT_SOURCE_DIR}/src/netFilterClient)

link_directories(${PROJECT_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

aux_source_directory(src/XML_PARSER xmlParser)
aux_source_directory(src/rvsDFA rvsDFA)
aux_source_directory(src/tinyxml2 tinyxml2)
aux_source_directory(src/netFilterClient netFilterClient)
aux_source_directory(src/serialForward serialForward)

set(src ${rvsDFA} ${tinyxml2} src/rvsDFATestSelf.cpp )

add_executable(rvs ${src})

target_link_libraries(rvs z3)