project(photo_get_project)
 
# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)
 
INCLUDE_DIRECTORIES(/usr/include/opencv2/)
INCLUDE_DIRECTORIES(/usr/include/opencv4/)
 
# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
 
# Declare the executable target built from your sources
add_executable(photo_get test.cpp)
 
# Link your application with OpenCV libraries
target_link_libraries(photo_get PRIVATE ${OpenCV_LIBS})

