#include "../helpHandler.hpp"


#include <exception>




int main(int argc, char** argv) {
    try {
        helpHandler::info("TestApp", "1.0"); //Also note that this is optional
        helpHandler::handleFile(argc, argv, "example_dialoge_file.txt"); //Similar to helpHandler::handle(), this will process arguments once called as well, but gets the help dialogue from a text file
    } catch(const std::exception& e) { std::cout << e.what(); }

    return EXIT_SUCCESS;
}
