cmake_minimum_required(VERSION 3.10)
project(FaceRecognition)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(face_recognition face_recognition.cpp)

# 添加Haar级联分类器的XML文件路径
set(CASCADES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cascades")


target_link_libraries(face_recognition ${OpenCV_LIBS})
