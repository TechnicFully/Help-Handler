#include <climits>
#include <gtest/gtest.h>

#include "../helpHandler.hpp"

#include <limits>
#include <random>
#include <string>
#include <iostream>
#include <exception>




static int random_num(int min, int max) {
    static std::default_random_engine rng;

    std::uniform_real_distribution<float> dist(min, max); 
    return dist(rng);
}





TEST(HelpHandler_handle, argcNegative) {
    char* argv[] = { "" };
    
    
    EXPECT_THROW({
        helpHandler::handle(-1, argv);
    }, std::invalid_argument);
}

TEST(HelpHandler_handle, argcZero) {
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
    EXPECT_THROW({
        helpHandler::config(-1);
    }, std::invalid_argument);

    for (int i = 0; i != 4096; i++) { //Magic number. No particular reason this was chosen
        EXPECT_THROW({
                int r = random_num(std::numeric_limits<int>::min(), -1);
                helpHandler::config(r);
        }, std::invalid_argument);
    }

}



TEST(HelpHandler_version, version) {
    EXPECT_THROW({
        helpHandler::version("");
    }, std::invalid_argument);

    EXPECT_THROW({
        helpHandler::version(" ");
    }, std::invalid_argument);
}



TEST(HelpHandler_name, appname) {
    EXPECT_THROW({
        helpHandler::name("");
    }, std::invalid_argument);

    EXPECT_THROW({
        helpHandler::name(" ");
    }, std::invalid_argument);

    //TODO: capture output of helpHandler::name(" 1 ");
}


TEST(HelpHandler_ReturnValues, handle) {
    int rvalue = -1; //Magic number. Return value is represented as an enum and therefore implicitly converted to an int, starting from 0. This prevents a false positive.

    char* argvHelpVersion[] = { "--help", "--version" };
    char* argvHelp[] = { "--help" };
    char* argvVersion[] = { "--version" };
    char* argvBlank[] = { "blank" };
    const char* dummy_dialogue = "dummy dialogue";


    rvalue = helpHandler::handle(4, argvHelpVersion, dummy_dialogue);
    ASSERT_EQ(rvalue, HELP_HANDLER_ALL_MATCHED);

    rvalue = helpHandler::handle(3, argvHelp, dummy_dialogue);
    ASSERT_EQ(rvalue, HELP_HANDLER_HELP_MATCHED);

    helpHandler::handle(3, argvVersion, dummy_dialogue);
    ASSERT_EQ(rvalue, HELP_HANDLER_VERSION_MATCHED);

    helpHandler::handle(3, argvBlank, dummy_dialogue);
    ASSERT_EQ(rvalue, HELP_HANDLER_NONE_MATCHED);
}




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
