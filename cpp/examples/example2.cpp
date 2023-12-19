#include "../helpHandler.hpp"


#include <exception>
#include <iostream>




int main(int argc, char** argv) {
    try {
        helpHandler::version("1.0"); //This must come before the main helpHandler::handle function, which is what processes the arguments
        helpHandler::handle(argc, argv, "usage: help dialogue example");
    } catch(const std::exception& e) { std::cout << e.what(); }

    return EXIT_SUCCESS;
}

