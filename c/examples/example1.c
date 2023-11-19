#include "../help_handler.h"

#include <stdlib.h>




int main(int argc, char** argv) {
    help_handler(argc, argv, "usage: help dialogue example"); //Set help dialogue and process arguments

    return EXIT_SUCCESS;
}
