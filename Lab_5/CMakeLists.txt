cmake_minimum_required(VERSION 2.8)
project(Lab_5_24)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Task1 Task1.cpp Functions.cpp)
add_executable(Task2 Task2.cpp Functions.cpp)



target_link_libraries(Task1 ${OpenCV_LIBS})
target_link_libraries(Task2 ${OpenCV_LIBS})


