#include <climits>
#include <gtest/gtest.h>

#include "../helpHandler.hpp"


#include <iostream>
#include <exception>




TEST(HelpHandler_handle, argc) {
    char* argv[] = { "" };
    

    EXPECT_THROW({
        helpHandler::handle(-1, argv);
    }, std::invalid_argument);
}

TEST(HelpHandler_handle, argv) {
    char* argv[] = { "" };
    

    EXPECT_THROW({
        helpHandler::handle(0, argv);
    }, std::invalid_argument);
}



TEST(HelpHandler_handleFile, fileName) {
    int argc = 1;
    char* argv[] = { "test" };

    EXPECT_THROW({
        helpHandler::handleFile(argc, argv, "thisFileShouldNotExist");
    }, std::ios_base::failure);

    EXPECT_THROW({
        helpHandler::handleFile(argc, argv, "emptyTestFile.txt");
    }, std::runtime_error);
}



TEST(HelpHandler_config, options) {
    //TODO: generate random numbers until given one that doesn't match any of the possible config int values

    EXPECT_THROW({
        helpHandler::config(-1);
    }, std::invalid_argument);
}



TEST(HelpHandler_version, version) {
    EXPECT_THROW({
        helpHandler::version("");
    }, std::invalid_argument);

    EXPECT_THROW({
        helpHandler::version(" ");
    }, std::invalid_argument);
}



TEST(HelpHandler_name, appName) {
    EXPECT_THROW({
        helpHandler::name("");
    }, std::invalid_argument);

    EXPECT_THROW({
        helpHandler::name(" ");
    }, std::invalid_argument);

    //TODO: capture output of helpHandler::name(" 1 ");
}




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
