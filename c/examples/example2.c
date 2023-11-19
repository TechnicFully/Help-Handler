#include "../help_handler.h"

#include <stdlib.h>




int main(int argc, char** argv) {
    help_handler_version("1.0"); //This must come before the main help_handler function, which is what processes the arguments
    help_handler(argc, argv, "usage: help dialogue example");

    return EXIT_SUCCESS;
}
