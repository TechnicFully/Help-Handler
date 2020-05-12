#include "help_handler.h"

#include <time.h>




int main(int argc, char** argv) {
    clock_t t;
    t = clock();
    
	help_handler(argc, argv, "Usage: Test\n", NULL, HELP_MATCH_EXTRA_STRINGS);
    
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; //in seconds
    printf("help_handler() exited in %f seconds\n", time_taken);
}
