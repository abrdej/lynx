cmake_minimum_required(VERSION 3.5.1)
project(lynx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

add_compile_options(-fPIC)

find_package(Boost COMPONENTS program_options log log_setup system REQUIRED)
find_package(TBB REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(src/lynx/logging)
add_subdirectory(src/lynx/net)
