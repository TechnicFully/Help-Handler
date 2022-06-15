#include <climits>
#include <gtest/gtest.h>

#include "../help_handler.h"


#include <iostream>
#include <exception>





TEST(HelpHandler_version, ver) {
    ASSERT_EQ(helpHandlerFailure, help_handler_version(NULL));
    ASSERT_EQ(helpHandlerFailure, help_handler_version(""));
    ASSERT_EQ(helpHandlerFailure, help_handler_version(" "));
    
    ASSERT_EQ(helpHandlerSuccess, help_handler_version(" test "));
}



TEST(HelpHandler_name, name) {
    ASSERT_EQ(helpHandlerFailure, help_handler_name(NULL));
    ASSERT_EQ(helpHandlerFailure, help_handler_name(""));
    ASSERT_EQ(helpHandlerFailure, help_handler_name(" "));

    ASSERT_EQ(helpHandlerSuccess, help_handler_name(" test "));
}



TEST(HelpHandler_pipe_s, output_pipe) {
    ASSERT_EQ(helpHandlerFailure, help_handler_pipe(NULL));
    ASSERT_EQ(helpHandlerFailure, help_handler_pipe(""));

    //This function's parameter is not sanitized (whitespace trimmed) as it's a config function, and so default behavior is to just succeed, setting stdout as the pipe (the default)
    ASSERT_EQ(helpHandlerSuccess, help_handler_pipe(" "));
}



TEST(HelpHandler_handle, argc) {
    //TODO: swap out helpHandlerFailure with specific error values later
    char* test[] = { "test" };

    ASSERT_EQ(helpHandlerFailure, help_handler(-1, test, "test"));
    ASSERT_EQ(helpHandlerFailure, help_handler(0, test, "test"));
    
    ASSERT_EQ(helpHandlerSuccess, help_handler(1, test, "test"));
}

TEST(HelpHandler_handle, argv) {
    char* argvEmpty[] = { "" };

    //Currently this SHOULD return failure, but as argc is 1 in this case, the code to check if argv is NULL is never reached. Should fix later
    ASSERT_EQ(helpHandlerFailure, help_handler(1, NULL, NULL)); 
    ASSERT_EQ(helpHandlerFailure, help_handler(1, NULL, "test"));

    ASSERT_EQ(helpHandlerFailure, help_handler(1, argvEmpty, NULL));
    ASSERT_EQ(helpHandlerFailure, help_handler(1, argvEmpty, "test"));


    ASSERT_EQ(helpHandlerFailure, help_handler(2, NULL, NULL)); 
    ASSERT_EQ(helpHandlerFailure, help_handler(2, NULL, "test"));

    ASSERT_EQ(helpHandlerFailure, help_handler(2, argvEmpty, NULL));
    ASSERT_EQ(helpHandlerFailure, help_handler(2, argvEmpty, "test"));
}

TEST(HelpHandler_handle, help_dialogue) {
    char* argv[] = { "test" };
    char* argvTwo[] = { "test1", "test2" };

    ASSERT_EQ(helpHandlerSuccess, help_handler(1, argv, NULL));
    ASSERT_EQ(helpHandlerSuccess, help_handler(1, argv, ""));
    ASSERT_EQ(helpHandlerSuccess, help_handler(1, argv, " "));
    ASSERT_EQ(helpHandlerSuccess, help_handler(1, argv, " test dialogue "));


    ASSERT_EQ(helpHandlerSuccess, help_handler(2, argvTwo, NULL));
    ASSERT_EQ(helpHandlerSuccess, help_handler(2, argvTwo, ""));
    ASSERT_EQ(helpHandlerSuccess, help_handler(2, argvTwo, " "));
    ASSERT_EQ(helpHandlerSuccess, help_handler(2, argvTwo, " test dialogue "));

}



TEST(HelpHandler_handle_f, file_name) {
    int argc = 1;
    char* argv[] = { "help" };

    ASSERT_EQ(helpHandlerFailure, help_handler_f(argc, argv, NULL));
    ASSERT_EQ(helpHandlerFailure, help_handler_f(argc, argv, ""));
    ASSERT_EQ(helpHandlerFailure, help_handler_f(argc, argv, " "));   
    ASSERT_EQ(helpHandlerFailure, help_handler_f(argc, argv, "thisFileShouldNotExist")); 
    ASSERT_EQ(helpHandlerFailure, help_handler_f(argc, argv, "emptyTestFile.txt"));

    ASSERT_EQ(helpHandlerSuccess, help_handler_f(argc, argv, "filledTestFile.txt"));
}



//Make sure this is the very last test, as it'll conflict with the expected behavior for the other tests
TEST(HelpHandler_config, option_flags) {
    //TODO: generate random numbers until given one that doesn't match any of the possible config int values
    ASSERT_EQ(helpHandlerFailure, help_handler_config(-1));

    //TODO: pass every possible combination of values. Not likely to be a bug, but still possible
    ASSERT_EQ(helpHandlerSuccess, help_handler_config(DISABLE_EXTRA_STRINGS));
    ASSERT_EQ(helpHandlerSuccess, help_handler_config(DISABLE_NO_ARGS_HELP));
    ASSERT_EQ(helpHandlerSuccess, help_handler_config(DISABLE_MATCH_HYPHENS));
    ASSERT_EQ(helpHandlerSuccess, help_handler_config(ENABLE_UNKNOWN_ARGS_HELP));
    ASSERT_EQ(helpHandlerSuccess, help_handler_config(ENABLE_HYPHENS_ONLY));
}




int main(int argc, char** argv) {
    help_handler_disable_err(true);

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
