#include "../helpHandler.hpp"


#include <exception>




int main(int argc, char** argv) {
    try {
        helpHandler::version("1.0"); //This must come before the main helpHandler::handle function, which is what actually processes arguments
        helpHandler::handle(argc, argv, "usage: help dialogue example");
    } catch(const std::exception& e) { std::cout << e.what(); }

    return EXIT_SUCCESS;
}
