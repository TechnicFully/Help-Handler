project(HelpHandlerTest CXX)
cmake_minimum_required(VERSION 2.9)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wno-write-strings")

add_executable(HelpHandlerTest main.cpp)
target_link_libraries(HelpHandlerTest ${GTEST_LIBRARIES} pthread)