cmake_minimum_required(VERSION 3.0)
project(MouseCallbackExample)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(mouse_callback_example main.cpp)
target_link_libraries(mouse_callback_example ${OpenCV_LIBS})
