#include "../help_handler.h"




int main(int argc, char** argv) {
    help_handler_info("TestApp", "1.0"); //Also note that this is optional
    help_handler_f(argc, argv, "example_dialoge_file.txt"); //Like help_handler(), this will process arguments once called as well, but gets the help dialogue from a text file


    return EXIT_SUCCESS;
}
