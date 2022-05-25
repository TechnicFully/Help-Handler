#include "../helpHandler.hpp"


#include <exception>




int main(int argc, char** argv) {
    try {
        helpHandler::config(ENABLE_HYPHENS_ONLY|DISABLE_MATCH_HYPHENS);
        helpHandler::handle(argc, argv, "usage: help dialogue example");
    } catch(const std::exception& e) { std::cout << e.what() << std::endl; }
    
    return EXIT_SUCCESS;
}

