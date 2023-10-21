cmake_minimum_required(VERSION 3.5.1)
project(lynx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

find_package(Boost COMPONENTS log log_setup system REQUIRED)
find_package(TBB REQUIRED)

add_library(lynx INTERFACE)
target_include_directories(lynx INTERFACE src)
target_link_libraries(lynx INTERFACE TBB::tbb log log_setup system)
