# cmake最低版本号要求
cmake_minimum_required(VERSION 3.6)

# 项目信息
project(runtime-verification-system)

# include路径
include_directories(${PROJECT_SOURCE_DIR}/lib)

# 第三方库的.a文件和.h文件目录
link_directories(${PROJECT_SOURCE_DIR}/lib)

# 设置可执行文件生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 设置生成的版本编译指令
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# 查找当前目录下所有源文件，并将名称保存到变量中
aux_source_directory(src DIR_SRCS)

# 指定生成目标
add_executable(runtime_verification-system ${DIR_SRCS})

# 连接第三方库
target_link_libraries(runtime_verification-system lib/libz3.dll.a)

#set(SOURCE_FILES src/main.cpp src/State.cpp src/State.h src/Trans.cpp src/Trans.h src/Module.cpp src/Module.h src/Spec.cpp src/Spec.h src/Vars.cpp src/Vars.h)
#add_executable(runtime-verification-system ${SOURCE_FILES})
#target_link_libraries(runtime-verfication-system lib/libz3.dll.a)