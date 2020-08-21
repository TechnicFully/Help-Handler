#include "../help_handler.h"

#include <time.h>




int main(int argc, char** argv) {
    clock_t t;
    t = clock();
    
    help_handler_config(1, 1, 1, "1.0.0\n");
    help_handler_ver("2.0.0\n");
    help_handler(argc, argv, "Usage: Test\n", NULL);
    
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; //In seconds
    printf("help_handler() exited in %f seconds\n", time_taken);
}
