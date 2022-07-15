project(HelpHandlerTest CXX)
cmake_minimum_required(VERSION 2.9)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wno-write-strings")
set(CMAKE_C_FLAGS "-fpermissive")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/emptyTestFile.txt ${CMAKE_CURRENT_BINARY_DIR}/emptyTestFile.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/filledTestFile.txt ${CMAKE_CURRENT_BINARY_DIR}/filledTestFile.txt COPYONLY)
add_definitions(-DHELP_HANDLER_DEBUG)

add_executable(HelpHandlerTest main.cpp)
target_link_libraries(HelpHandlerTest ${GTEST_LIBRARIES} pthread)
