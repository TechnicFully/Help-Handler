#include "../help_handler.h"

#include <stdlib.h>




int main(int argc, char** argv) {
    help_handler_info("AppTest", "1.0"); //This is self-explanatory: the info() and version() functions combined for convenience
    help_handler(argc, argv, "usage: help dialogue example");

    return EXIT_SUCCESS;
}
