#include "../helpHandler.hpp"


#include <exception>
#include <iostream>




int main(int argc, char** argv) {
    int return_value;

    try {
        helpHandler::info("TestApp", "1.0");
        return_value = helpHandler::handle(argc, argv); //We can also ONLY check what happened by not passing any help dialogue argument, and no help dialogue will be output

        if (HELP_HANDLER_ALL_MATCHED == return_value) { //This will only have output the program version (1.0), only because it was set above
            std::cout << "Help and version arguments were found";
        } else if (HELP_HANDLER_HELP_MATCHED == return_value) { //This will have output nothing
            std::cout << "Only help arguments were found";
        } else if (HELP_HANDLER_VERSION_MATCHED == return_value) { //This will also have output the program version
            std::cout << "Only version arguments were found";
        } else if (HELP_HANDLER_NONE_MATCHED == return_value) { //This will have output nothing
            std::cout << "No arguments were found";
        }

        #ifdef _WIN32
        std::cout << "\r\n" << std::flush;
        #else
        std::cout << std::endl;
        #endif

    } catch(const std::exception& e) { std::cout << e.what(); }

    return return_value;
}
