cmake_minimum_required(VERSION 3.0)
project(PerspectiveTransformationExample)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(perspective_transform_example main.cpp)
target_link_libraries(perspective_transform_example ${OpenCV_LIBS})
