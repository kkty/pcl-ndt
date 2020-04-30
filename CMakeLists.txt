cmake_minimum_required (VERSION 2.8.11)
project (NDT)

set (CMAKE_CXX_STANDARD 14)
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(main main.cpp)
target_link_libraries(main ${PCL_LIBRARIES})

