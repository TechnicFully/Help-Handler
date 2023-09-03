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
