#include "../help_handler.h"

#include <stdlib.h>




int main(int argc, char** argv) {
    help_handler_name("AppTest"); //This must also come before help_handler(), however it doesn't matter if it's called/set before or after help_handler_version()
    help_handler_version("1.0");
    help_handler(argc, argv, "usage: help dialogue example");

    return EXIT_SUCCESS;
}
