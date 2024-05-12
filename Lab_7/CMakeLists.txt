cmake_minimum_required(VERSION 2.8)
project(Lab_7_24)
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_STANDARD 14)
find_package( Boost COMPONENTS filesystem REQUIRED )
find_package(OpenCV REQUIRED)


set(SRCS src/Panorama.cpp src/Utils.cpp PanoramicUtils/panoramic_utils.cpp)
add_library(${PROJECT_NAME} ${SRCS})
target_include_directories( ${PROJECT_NAME} PUBLIC
        src
        PanoramicUtils
        include
        ${OpenCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
        ${Boost_LIBRARIES}
        ${OpenCV_LIBS})

add_executable(Panorama src/Panorama_app.cpp)
target_link_libraries(Panorama ${PROJECT_NAME})
set_target_properties(Panorama PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)



