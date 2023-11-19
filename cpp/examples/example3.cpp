#include "../helpHandler.hpp"


#include <exception>




int main(int argc, char** argv) {
    try {
        helpHandler::name("TestApp"); //This sets the application name and must also come before helpHandler::handle(), however it doesn't matter if it's called before or after helpHandler::version()
        helpHandler::version("1.0");
        helpHandler::handle(argc, argv, "usage: help dialogue example");
    } catch(const std::exception& e) { std::cout << e.what(); }

    return EXIT_SUCCESS;
}

