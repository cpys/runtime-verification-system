cmake_minimum_required(VERSION 3.6)
project(runtime-verification-system)

include_directories(${PROJECT_SOURCE_DIR}/api)

link_directories(${PROJECT_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#aux_source_directory(src DIR_SRCS)

set(DIR_SRCS src/xmlParser/xmlParserTest.cpp src/xmlParser/XmlParser.cpp src/xmlParser/tinyxml2.cpp src/DFA/Module.cpp src/DFA/State.cpp src/DFA/States.cpp src/DFA/Tran.cpp src/DFA/Trans.cpp src/DFA/Vars.cpp)

add_executable(rvs ${DIR_SRCS})

target_link_libraries(rvs libz3.dll)