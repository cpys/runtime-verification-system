cmake_minimum_required(VERSION 3.6)
project(runtime-verification-system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/State.cpp src/State.h src/Trans.cpp src/Trans.h src/Module.cpp src/Module.h src/Spec.cpp src/Spec.h src/Vars.cpp src/Vars.h)
add_executable(runtime-verification-system ${SOURCE_FILES})
#target_link_libraries(runtime-verfication-system lib/libz3.dll.a)