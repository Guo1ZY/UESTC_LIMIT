# PROJECT(VISUALIZATION_TEST)
# CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
# FIND_PACKAGE(PCL 1.3 REQUIRED)
# INCLUDE_DIRECTORIES({PCL_INCLUDE_DIRS})
# link_directories(${PCL_LIBRARY_DIRS})
# add_definitions(${PCL_DEFINITIONS})
# add_executable(run main.cpp)
# target_link_libraries(run ${PCL_COMMON_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES})
cmake_minimum_required(VERSION 3.0)
project(PointCloudVisualization)

# 设置C++编译标准为C++11
set(CMAKE_CXX_STANDARD 11)

# 查找PCL库
find_package(PCL 1.2 REQUIRED)

# 添加包含目录
include_directories(${PCL_INCLUDE_DIRS})

# 添加库目录
link_directories(${PCL_LIBRARY_DIRS})

# 添加可执行文件
add_executable(PointCloudViewer main.cpp)

# 链接PCL库
target_link_libraries(PointCloudViewer ${PCL_LIBRARIES})
