#include "../helpHandler.hpp"


#include <exception>




int main(int argc, char** argv) {
    try {
        int rval = helpHandler::handle(argc, argv, "usage: help dialogue example"); //Set help dialogue and process arguments
    } catch(const std::exception& e) { std::cout << e.what() << std::endl; }
    
    return EXIT_SUCCESS;
}

