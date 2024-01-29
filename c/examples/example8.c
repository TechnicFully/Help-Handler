#include "../help_handler.h"

#include <stdio.h>




int main(int argc, char** argv) {
    int return_value;

    help_handler_info("TestApp", "1.0");
    help_handler_config(DISABLE_NO_ARGS_HELP); //Disable output of help dialogue if the user passes no arguments
    return_value = help_handler(argc, argv, NULL); //We can also then ONLY check what happened with a NULL value, and no help dialogue will be output

    if (HELP_HANDLER_ALL_MATCHED == return_value) { //This will only have output the program version (1.0), only because it was set above
        printf("Help and version arguments were found");
    } else if (HELP_HANDLER_HELP_MATCHED == return_value) { //This will have output nothing
        printf("Only help arguments were found");
    } else if (HELP_HANDLER_VERSION_MATCHED == return_value) { //This will also have output the program version
        printf("Only version arguments were found");
    } else if (HELP_HANDLER_NONE_MATCHED == return_value) { //This will have output nothing
        printf("No arguments were found");
    }


    printf("\n");

    return return_value;
}
