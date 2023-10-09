
project(cam)  
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 如果找到了OpenCV包，将设置多个变量
# 您可以在OpenCVConfig.cmake文件中找到完整的变量列表和描述
# 打印一些消息来显示其中一些变量
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# 声明从您的源文件构建的可执行目标
add_executable(cam "main.cpp")

# 链接您的应用程序与OpenCV库
target_link_libraries(cam PRIVATE ${OpenCV_LIBS})


