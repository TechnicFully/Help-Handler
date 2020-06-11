#include "../help_handler.hpp"




int main(int argc, char** argv) {
    helpHandlerConfig(true, true, true, "1.0.0");
    helpHandler(argc, argv, "Usage: Test");

    return EXIT_SUCCESS;
    
}

