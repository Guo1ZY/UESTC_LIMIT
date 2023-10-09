# project name
PROJECT(HELLO)

# using C++11
set(SRC_LIST  "hello.cpp")
# cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
# find OpenCV
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES({OpenCV_INCLUDE_DIRS})
# 生成可执行文件
ADD_EXECUTABLE(hello ${SRC_LIST})
# after ADD_EXECUTABLE，为生成文件target添加库
TARGET_LINK_LIBRARIES(hello ${OpenCV_LIBS})


