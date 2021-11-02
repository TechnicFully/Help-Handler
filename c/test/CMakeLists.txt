project(HelpHandlerTest CXX)
cmake_minimum_required(VERSION 2.9)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

add_executable(HelpHandlerTest gtest.cpp)
target_link_libraries(HelpHandlerTest ${GTEST_LIBRARIES} pthread)