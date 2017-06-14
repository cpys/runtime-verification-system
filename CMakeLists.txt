cmake_minimum_required(VERSION 3.6)
project(runtime-verification-system)

include_directories(${PROJECT_SOURCE_DIR}/api)
include_directories(${PROJECT_SOURCE_DIR}/src/rvsDFAInterface)
include_directories(${PROJECT_SOURCE_DIR}/src/rvsDFA/headers)
include_directories(${PROJECT_SOURCE_DIR}/src/tinyxml2)
include_directories(${PROJECT_SOURCE_DIR}/src/netFilterClient)

link_directories(${PROJECT_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#aux_source_directory(src DIR_SRCS)

aux_source_directory(src/XML_PARSER xmlParser)
aux_source_directory(src/DFA DFA)
aux_source_directory(src/newDFA newDFA)
aux_source_directory(src/rvsDFA rvsDFA)
aux_source_directory(src/tinyxml2 tinyxml2)
aux_source_directory(src/netFilterClient netFilterClient)

set(src ${rvsDFA} ${tinyxml2} ${netFilterClient} src/rvsDFATest2.cpp )

add_executable(rvs ${src})

target_link_libraries(rvs libz3.so)