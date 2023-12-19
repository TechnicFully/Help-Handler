#include "../helpHandler.hpp"


#include <exception>
#include <iostream>




int main(int argc, char** argv) {
    try {
        helpHandler::info("TestApp", "1.0"); //This is self-explanatory, being the name() and version() functions combined for convenience
        helpHandler::handle(argc, argv, "usage: help dialogue example");
    } catch(const std::exception& e) { std::cout << e.what(); }

    return EXIT_SUCCESS;
}

