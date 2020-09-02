#include "../helpHandler.hpp"




int main(int argc, char** argv) {
    helpHandler::config(true, true, true, "1.0.0");
    helpHandler::ver("2.0.0");
    helpHandler::handle(argc, argv, "Usage: Test");

    return EXIT_SUCCESS;
    
}

