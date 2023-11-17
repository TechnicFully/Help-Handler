#include "../helpHandler.hpp"


#include <exception>




int main(int argc, char** argv) {
    try {
        helpHandler::info("TestApp", "1.0");
        helpHandler::config(DISABLE_EXTRA_STRINGS); //Disables matching abbreviated arguments, v, -v, --v, h, -h, --h
                                                    //You can also pass...
                                                    //  DISABLE_NO_ARGS_HELP
                                                    //  DISABLE_MATCH_HYPHENS
                                                    //  ENABLE_UNKNOWN_ARGS_HELP
                                                    //  ENABLE_HYPHENS_ONLY

        helpHandler::handle(argc, argv, "usage: help dialogue example");
    } catch(const std::exception& e) { std::cout << e.what(); }

    return EXIT_SUCCESS;
}
