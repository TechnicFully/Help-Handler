#include "../helpHandler.hpp"


#include <exception>




int main(int argc, char** argv) {
    try {
        helpHandler::version("1.0");
        helpHandler::handle(argc, argv, "usage: example");
    } catch(const std::exception& e) { std::cout << e.what(); }
    return EXIT_SUCCESS;
}

