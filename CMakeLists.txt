cmake_minimum_required(VERSION 3.6)
project(runtime-verification-system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp State.cpp State.h Trans.cpp Trans.h Module.cpp Module.h Spec.cpp Spec.h Vars.cpp Vars.h)
add_executable(runtime-verification-system ${SOURCE_FILES})