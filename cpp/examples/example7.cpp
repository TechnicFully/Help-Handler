#include "../helpHandler.hpp"


#include <exception>
#include <iostream>




int main(int argc, char** argv) {
    int return_value;

    try {
        helpHandler::info("TestApp", "1.0");
        return_value = helpHandler::handle(argc, argv, "usage: help dialogue example"); //This time, let's catch the return value and check what happened...

        if (HELP_HANDLER_ALL_MATCHED == return_value) {
            std::cout << "Help and version arguments were found";
        } else if (HELP_HANDLER_HELP_MATCHED == return_value) {
            std::cout << "Only help arguments were found";
        } else if (HELP_HANDLER_VERSION_MATCHED == return_value) {
            std::cout << "Only version arguments were found";
        } else if (HELP_HANDLER_NONE_MATCHED == return_value) {
            std::cout << "No arguments were found";
        } //These are all the possible return values

        #ifdef _WIN32
        std::cout << "\r\n" << std::flush;
        #else
        std::cout << std::endl;
        #endif

    } catch(const std::exception& e) { std::cout << e.what(); }

    return return_value;
}
