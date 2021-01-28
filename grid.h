#include <stdio.h>
#include <stdlib.h>

#ifndef GRID_H
#define GRID_H

typedef struct Grid
{
    /* data */
    char* grid;
    int length;

} Grid;

Grid* init_grid(int length);

void set_random_state(Grid* g, int random_alive_fraction);

void run_single_iteration(Grid* g);

char* get_current_grid(Grid* g); 

void delete_grid(Grid* g);

void print_grid(Grid* g, FILE* f);

#endif // GRID_H