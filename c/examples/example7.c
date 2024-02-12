#include "../help_handler.h"

#include <stdio.h>




int main(int argc, char** argv) {
    int return_value;

    help_handler_info("TestApp", "1.0");
    return_value = help_handler(argc, argv, "usage: help dialogue example"); //This time, let's catch the return value and check what happened...

    if (HELP_HANDLER_ALL_MATCHED == return_value) {
        printf("Help and version arguments were found");
    } else if (HELP_HANDLER_HELP_MATCHED == return_value) {
        printf("Only help arguments were found");
    } else if (HELP_HANDLER_VERSION_MATCHED == return_value) {
        printf("Only version arguments were found");
    } else if (HELP_HANDLER_NONE_MATCHED == return_value) {
        printf("No arguments were found");
    } //These are all the possible return values


    #ifdef _WIN32
    printf("\n\n");
    #else
    printf("\n");
    #endif

    return return_value;
}
