cmake_policy(SET CMP0048 NEW)
project(HelpHandlerTest LANGUAGES CXX C VERSION 0.1.0 HOMEPAGE_URL https://github.com/TechnicFully/Help-Handler DESCRIPTION "A one-file library to accomplish the simple task of outputting help dialogue and/or version information to be used with other libraries, in numerous programming languages.")
cmake_minimum_required(VERSION 2.9)



###Settings
add_definitions(-DHELP_HANDLER_DEBUG)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/emptyTestFile.txt ${CMAKE_CURRENT_BINARY_DIR}/emptyTestFile.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/filledTestFile.txt ${CMAKE_CURRENT_BINARY_DIR}/filledTestFile.txt COPYONLY)




###Add GTest
enable_testing()

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip #Last version to support C++11
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) #For Windows: prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

include(GoogleTest)




###Finish
add_executable(HelpHandlerTest main.cpp)
target_include_directories(HelpHandlerTest PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(HelpHandlerTest PRIVATE GTest::gtest_main pthread -fsanitize=address)
target_compile_options(HelpHandlerTest PRIVATE -Wall -Wextra -pedantic -Wconversion -fstack-protector-all -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wformat=2 -Wshadow -fwrapv -Wunreachable-code -fsanitize=address -g3 -Wno-write-strings -fpermissive)


add_executable(HelpHandlerTestC99 main.cpp)
target_include_directories(HelpHandlerTestC99 PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(HelpHandlerTestC99 PRIVATE GTest::gtest_main pthread -fsanitize=address)
target_compile_options(HelpHandlerTestC99 PRIVATE -Wall -Wextra -pedantic -Wconversion -fstack-protector-all -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wformat=2 -Wshadow -fwrapv -Wunreachable-code -fsanitize=address -g3 -Wno-write-strings -fpermissive)
set_property(TARGET HelpHandlerTestC99 PROPERTY C_STANDARD 99)
