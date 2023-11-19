#include "../help_handler.h"




int main(int argc, char** argv) {
    help_handler_info("TestApp", "1.0"); //Also note that this is optional
    help_handler_config(DISABLE_EXTRA_STRINGS); //Disables matching abbreviated arguments, v, -v, --v, h, -h, --h
                                                //You can also pass...
                                                //  DISABLE_NO_ARGS_HELP
                                                //  DISABLE_MATCH_HYPHENS
                                                //  ENABLE_UNKNOWN_ARGS_HELP
                                                //  ENABLE_HYPHENS_ONLY

    help_handler(argc, argv, "usage: help dialogue example");

    return EXIT_SUCCESS;
}
