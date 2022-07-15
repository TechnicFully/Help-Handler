project(HelpHandlerTest CXX)
cmake_minimum_required(VERSION 2.9)


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wno-write-strings -fpermissive")

add_executable(HelpHandlerTest main.cpp)

target_link_libraries(HelpHandlerTest ${GTEST_LIBRARIES} pthread -fsanitize=address)
target_compile_options(HelpHandlerTest PRIVATE -Wall -Wextra -pedantic -Wconversion -fstack-protector-all -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wformat=2 -Wshadow -fwrapv -Werror=implicit-function-declaration -Wunreachable-code -fsanitize=address -g3 -std=c++11)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/emptyTestFile.txt ${CMAKE_CURRENT_BINARY_DIR}/emptyTestFile.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/filledTestFile.txt ${CMAKE_CURRENT_BINARY_DIR}/filledTestFile.txt COPYONLY)
