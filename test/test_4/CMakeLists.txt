# 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目信息
project(opencv_demo)

# 使用find_package命令查找OpenCV库
find_package(OpenCV REQUIRED)
find_package(gflags REQUIRED)

if (OpenCV_FOUND)
    message(STATUS "OpenCV library status:")
    message(STATUS "    version: ${OpenCV_VERSION}")
    message(STATUS "    libraries: ${OpenCV_LIBS}")
    message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Could not find OpenCV library")
endif()

# 添加头文件
include_directories(${OpenCV_INCLUDE_DIRS} ${gflags_INCLUDE_DIRS})
# 链接库
link_libraries(${OpenCV_LIBS} ${gflags_LIBRARIES})


