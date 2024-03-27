cmake_minimum_required(VERSION 2.8)
project(Lab_2_24)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
include_directories(${OpenCV_INCLUDE_DIRS})

#set(SOURCE_FILES task1.cpp)

add_executable(Task1 Task1.cpp Functions.cpp)
add_executable(Task2 Task2.cpp ImageFilters.cpp Functions.cpp)
add_executable(Task3 Task3.cpp ImageFilters.cpp Functions.cpp)
add_executable(Task4 Task4.cpp ImageFilters.cpp Functions.cpp)
add_executable(Task5 Task5.cpp Functions.cpp)
add_executable(Task6 Task6.cpp Functions.cpp)

target_link_libraries(Task1 ${OpenCV_LIBS})
target_link_libraries(Task2 ${OpenCV_LIBS})
target_link_libraries(Task3 ${OpenCV_LIBS})
target_link_libraries(Task4 ${OpenCV_LIBS})
target_link_libraries(Task5 ${OpenCV_LIBS})
target_link_libraries(Task6 ${OpenCV_LIBS})

