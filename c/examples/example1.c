#include "../help_handler.h"

#include <stdlib.h>




int main(int argc, char** argv) {
    help_handler_version("1.0");
    help_handler(argc, argv, "Usage: Help");

    return EXIT_SUCCESS;
}