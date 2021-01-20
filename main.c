#include <stdio.h>
#include <stdlib.h>

#include "grid.h"

#define ITERATIONS 10



int main(int argc, char** argv) {
    Grid* g = init_grid();
    set_random_state(g);
    for (int i = 0; i < ITERATIONS; i++ ) {
        print_grid(g, stdout);
        run_single_iteration(g);
        fprintf(stdout, "FINISHED ITERATION \n\n");
    }

}