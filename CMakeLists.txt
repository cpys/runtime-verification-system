cmake_minimum_required(VERSION 3.6)
project(runtime-verification-system)

include_directories(${PROJECT_SOURCE_DIR}/api)
#include_directories(${PROJECT_SOURCE_DIR}/src/DFAInterface)
#include_directories(${PROJECT_SOURCE_DIR}/src/newDFA/headers)

link_directories(${PROJECT_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#aux_source_directory(src DIR_SRCS)

set(XML_PARSER src/xmlParser/tinyxml2.cpp src/xmlParser/XmlParser.cpp)
set(DFA src/DFA/Module.cpp src/DFA/State.cpp src/DFA/States.cpp src/DFA/Tran.cpp src/DFA/Trans.cpp src/DFA/Vars.cpp)
set(newDFA src/newDFA/DFAModule.cpp src/newDFA/DFASpec.cpp src/newDFA/DFAState.cpp src/newDFA/DFAVar.cpp)

set(DIR_SRCS src/rvsDFAInterface/Module.h src/rvsDFAInterface/State.h src/rvsDFAInterface/Event.h src/rvsDFAInterface/Tran.h src/rvsDFA/DFAModule.cpp src/rvsDFA/DFAModule.h src/rvsDFA/DFAState.cpp src/rvsDFA/DFAState.h src/rvsDFA/DFATran.cpp src/rvsDFA/DFATran.h src/rvsDFAInterface/Spec.h src/rvsDFA/DFASpec.cpp src/rvsDFA/DFASpec.h src/rvsDFA/DFAEvent.cpp src/rvsDFA/DFAEvent.h)


add_executable(rvs ${DIR_SRCS})

target_link_libraries(rvs libz3.so)