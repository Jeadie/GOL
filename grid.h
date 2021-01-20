#include <stdio.h>
#include <stdlib.h>

#ifndef GRID_H
#define GRID_H

#define LENGTH 10

typedef struct Grid
{
    /* data */
    char* grid;

} Grid;

Grid* init_grid(void);

void set_random_state(Grid* g);

void run_single_iteration(Grid* g);

char* get_current_grid(Grid* g); 

void delete_grid(Grid* g);

void print_grid(Grid* g, FILE* f);

#endif // GRID_H