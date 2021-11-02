#define HELP_HANDLER_IGNORE_ALL
#include "../help_handler.h"

#include <limits>
#include <gtest/gtest.h>




TEST(HelpHandler, Argc) {
    char** argv = {0};
    ASSERT_LT(help_handler(0, argv, NULL), 0);
    ASSERT_EQ(help_handler(std::numeric_limits<int>::max(), argv, NULL), helpHandlerFailure);
}

TEST(HelpHandler, Argv) {
    char** argv = {0};
    ASSERT_LT(help_handler(2, NULL, NULL), 0);
}

TEST(HelpHandler, HelpDialogue) {
    char* argv[] = { (char*)"--help", (char*)"--version" };
    ASSERT_EQ(help_handler(3, argv, NULL), 2);

}

TEST(HelpHandlerVersion, Version) {
    ASSERT_EQ(help_handler_version(NULL), -1);
    ASSERT_EQ(help_handler_version(""), -1);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}