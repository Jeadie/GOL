#include <stdio.h>
#include <stdlib.h>

#include "grid.h"


int main(int argc, char** argv) {

    int ITERATIONS = 100;
    int GRID_SIZE = 20;
    int RANDOM_START_STATE = 80;
    int MILLISECONDS_SLEEP = 200;

    if (argc >= 3) {
        ITERATIONS = atoi(argv[1]);
        GRID_SIZE = atoi(argv[2]);
    }
    if (argc == 5) {
        RANDOM_START_STATE = atoi(argv[3]);
        MILLISECONDS_SLEEP = atoi(argv[4]);
    }

    Grid* g = init_grid(GRID_SIZE);
    set_random_state(g, RANDOM_START_STATE);

    for (int i = 0; i < ITERATIONS; i++ ) {
        print_grid(g, stdout);
        if (run_single_iteration(g)){
            exit(0);
        };
        usleep(MILLISECONDS_SLEEP * 1000);
    }

}