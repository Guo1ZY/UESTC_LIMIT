## 注：这份文件包含了一些我们机器人队常用的库
## 如：ZED——双目摄像头库  OpenCV——图像处理库  CUDA——显卡加速库  Threads——多线程库
## PCL——点云处理库 Slamtec——思岚雷达库
## 各位后续可以基于此CMake文件稍作修改作为自己的CMake文件使用，不需要重复造轮子
## 但是需要能根据自己编写的代码进行调整
##后续含有自己写的注释--GouZY

CMAKE_MINIMUM_REQUIRED(VERSION 3.5)##cmake 所需的最小版本为3.5，由终端下载的cmake 版本为3.16，所以不用担心

PROJECT(lidar)##自定义project的名字为lidar,和雷达有关的CMakeLists.txt

option(LINK_SHARED_ZED "Link with the ZED SDK shared executable" ON)##定义一个CMake选项，用于控制是否链接ZED SDK的共享库。默认情况下，设置为ON，表示要链接共享库。
option(ENABLE_CUDA "" ON)##在默认情况下，cuda设置为打开

if (NOT LINK_SHARED_ZED AND MSVC)
    message(FATAL_ERROR "LINK_SHARED_ZED OFF : ZED SDK static libraries not available on Windows")##如果双目摄像库为off 为假且正在使用Microsoft Visual C++编译器（MSVC），则发出致命错误消息，指示ZED SDK的静态库在Windows上不可用。（不是linux?）直接终止程序
endif()


SET(EXECUTABLE_OUTPUT_PATH ".")##设置可执行文件的输出路径为当前目录。注意"."的意思为当前目录
SET(CUDA_NVCC_FLAGS -gencode arch=compute_53,code=sm_53)##设置CUDA编译器选项，指定CUDA代码生成选项，这里设置了计算能力 5.3 的选项。（chatgpt的解释）

set(CMAKE_CXX_FLAGS "-lstdc++ -pthread" )##set(CMAKE_CXX_FLAGS "-lstdc++ -pthread" )：设置C++编译器标志，包括链接标准C++库和线程库。
#set(CMAKE_BUILD_TYPE Release)##设置构建类型为release，这意味着在构建期间将启用调试信息。
set(CMAKE_BUILD_TYPE Debug)##设置构建类型为Debug，这意味着在构建期间将启用调试信息。debug 为默认状况下进行编译的选项
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")##设置C++编译器标志，指定C++标准版本为C++17并启用所有警告。
set(CMAKE_CXX_FLAGS_RELEASE  "-std=c++17 -O3")##设置在Release模式下的C++编译器标志，包括C++17标准和优化级别O3。

##语法  set( ${variable}  value )

find_package(ZED 3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(CUDA 11.2)
find_package(Threads REQUIRED)
find_package(PCL 1.10 REQUIRED COMPONENTS common io visualization)
find_package(PCL 1.10 REQUIRED)
##通过CMake查找所需的外部库。在这里，找到了ZED、OpenCV、CUDA、Threads、PCL库，并指定了它们的版本和组件。语法   find_package( XXXX_version required)
IF(NOT WIN32)
    add_definitions(-Wno-format-extra-args)
    SET(SPECIAL_OS_LIBS "pthread" "X11")
ENDIF()##如果不是win32 的操作系统(linux)，那么在不是Windows的操作系统上，设置了一个变量 SPECIAL_OS_LIBS，它包含了要链接的额外库的名称。在这里，它包括了 "pthread" 和 "X11" 库，这些库通常用于多线程和图形界面编程。这些库将在构建项目时与可执行文件一起链接，以便在运行时使用它们的功能。

include_directories(${CUDA_INCLUDE_DIRS})
include_directories(${ZED_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PCL_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/slamtec/include/)
include_directories(include)

##include_directories：添加包含目录，以便编译器可以找到所需的头文件。

link_directories(${ZED_LIBRARY_DIR})
link_directories(${CUDA_LIBRARY_DIRS})
link_directories(${PCL_LIBRARY_DIRS})##link_directories：添加库目录，以便链接器可以找到所需的库文件。
link_directories(${PROJECT_SOURCE_DIR}/slamtec/share/)
add_definitions(${PCL_DEFINITIONS})

LIST(APPEND CUDA_NVCC_FLAGS -std=c++14;-O2)##LIST(APPEND CUDA_NVCC_FLAGS -std=c++14;-O2)：这行代码向 CUDA_NVCC_FLAGS 列表中追加了编译CUDA代码的选项。具体来说，它设置了CUDA编译器的标准版本为C++14（-std=c++14）并启用了优化级别O2（-O2）
LIST(APPEND CUDA_NVCC_FLAGS -Xcompiler;-fPIC)##LIST(APPEND CUDA_NVCC_FLAGS -Xcompiler;-fPIC)：同样是向 CUDA_NVCC_FLAGS 列表中追加了编译CUDA代码的选项。这里使用了 -Xcompiler 选项来传递编译器选项给CUDA编译器，其中 -fPIC 用于生成位置无关的代码，通常用于共享库的构建。

SET(CUDA_PROPAGATE_HOST_FLAGS OFF)##SET(CUDA_PROPAGATE_HOST_FLAGS OFF)：此行将CUDA_PROPAGATE_HOST_FLAGS设置为OFF。这意味着CUDA编译器将不会传递主机编译器的标志（如C++标准和优化级别）给CUDA编译器。这通常是为了避免主机编译器的标志影响CUDA代码的编译。

LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_50,code=sm_50)
LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_60,code=sm_60)##两行将用于GPU架构代码生成的选项添加到 CUDA_NVCC_FLAGS 中。这表示CUDA编译器将为计算能力（architecture）50（Pascal架构）和60（Volta架构）生成对应的代码。

FILE(GLOB_RECURSE SRC_FILES src/*.cpp)
FILE(GLOB_RECURSE HDR_FILES include/*.hpp)##这两行代码用于查找项目源代码和头文件。它们使用 GLOB_RECURSE 来递归地搜索指定目录中的所有符合条件的文件，并将它们存储在 SRC_FILES 和 HDR_FILES 列表中。

CUDA_ADD_EXECUTABLE(r2 main.cpp ${HDR_FILES} ${SRC_FILES})##这行代码使用CUDA编译器创建一个名为 "r2" 的可执行文件，编译的源文件包括 "main.cpp" 以及通过 GLOB_RECURSE 找到的源文件和头文件。
add_definitions(-std=c++14 -O2)##将C++标准设置为C++14和启用优化级别O2。

if (LINK_SHARED_ZED)
    SET(ZED_LIBS ${ZED_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_CUDART_LIBRARY})
else()
    SET(ZED_LIBS ${ZED_STATIC_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_LIBRARY})
endif()
##这些代码根据 LINK_SHARED_ZED 变量的值来设置链接ZED SDK库的方式。如果 LINK_SHARED_ZED 为真（ON），则将链接共享库，否则将链接静态库。ZED_LIBS 变量包含了ZED库、CUDA的相关库以及其他可能的依赖项。
target_link_libraries(r2 ${ZED_LIBS})
target_link_libraries(r2 ${OpenCV_LIBS})
target_link_libraries(r2 Threads::Threads)
target_link_libraries(r2 ${PCL_LIBRARIES})
target_link_libraries(r2 ${PROJECT_SOURCE_DIR}/slamtec/share/libsl_lidar_sdk.a)##这些行用于将不同的库链接到生成的可执行文件 "r2" 中。它们链接了ZED、OpenCV、线程库、PCL和一个自定义的库 "libsl_lidar_sdk.a"。这确保了在构建可执行文件时正确链接所需的库。
