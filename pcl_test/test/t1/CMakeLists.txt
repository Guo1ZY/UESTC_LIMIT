cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(pcl_visualization_example)

find_package(PCL 1.13 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(pcl_visualization_example pcl_visualization_example.cpp)
target_link_libraries(pcl_visualization_example ${PCL_COMMON_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES})
