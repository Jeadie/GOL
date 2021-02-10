#include <stdio.h>
#include <stdlib.h>

#include "grid.h"

#define get_current_cell_value(g, x, y) (g->grid[x*g->length + y] & CURRENT_FLAG)
#define set_current_cell_value(g, x, y, value)  g->grid[x*g->length + y] = (g->grid[x*g->length + y] & NEXT_FLAG) | (CURRENT_FLAG & value);

#define get_next_cell_value(g, x, y) ((g->grid[x*g->length + y] & NEXT_FLAG) >> 4)
#define set_next_cell_value(g, x, y, value) g->grid[x*g->length + y] = (g->grid[x*g->length + y] & CURRENT_FLAG) | (NEXT_FLAG & (value << 4));


/**
 * Initialises the Grid struct.
 * 
 */
Grid* init_grid(int length) {
    Grid* g = (Grid*) malloc(sizeof(Grid));
    g->grid = (char*) malloc(length * length * sizeof(char));
    g->length = length;
    return g;
}

/**
 * Gets the number of alive neighbours for a given cell. 
 * 
 */
int get_number_of_live_neighbours(Grid* g, int x, int y){
    int count = 0;
    count += (x != 0 && get_current_cell_value(g,x-1, y)); 
    count += (y != 0 && get_current_cell_value(g,x, y-1));
    count += (y != g->length && get_current_cell_value(g,x, y+1));
    count += (x != g->length && get_current_cell_value(g,x+1, y));
    return count; 
}

/**
 * Updates all cells in the Grid g by setting the current value of each cell to its 
 * current next value. Does not clear the next value of any cell (the 4 leftmost 
 * bits).
 * 
 * Returns: The number of cells that changed value.
 *
 */
int update_cells(Grid* g) {
    int has_changed = 0;

    for(int i=1; i < g->length-1; i++) {
        for(int j=1; j < g->length-1; j++) {
            has_changed += get_next_cell_value(g,i,j) ^ get_current_cell_value(g,i,j);
            set_current_cell_value(g,i,j, get_next_cell_value(g,i,j));
        }
    }
    return has_changed;
}

/**
 * Computes the next status of a cell; i.e. the Game of Life update rule.
 */
char compute_next_status(char current_status, int live_neighbours) {
    return (current_status & (live_neighbours == 2 || live_neighbours == 3)) || (!current_status & (live_neighbours == 3));
}

/**
 * Runs a single iteration of Game of Life.
 * 
 * Returns: 1 if this single iteration changed no cells, 0 otherwise.
 */
int run_single_iteration(Grid* g) {
    for(int i=1; i < g->length-1; i++) {
        for(int j=1; j < g->length-1; j++) {
            char current_status = get_current_cell_value(g, i, j);
            int live_neighbours = get_number_of_live_neighbours(g, i, j);
            char next_status = compute_next_status(current_status, live_neighbours);

            // Sets grid cell so that next status is at the 4 leftmost bits.
            set_next_cell_value(g, i, j, next_status);
        }
    }
    return (update_cells(g) == 0);
}

/**
 * Deletes the Grid struct and all associated memory.  
 * 
 */
void delete_grid(Grid* g){
    free(g->grid);
    free(g);
}


/**
 * Prints the grid to the file. Function prints grid with terminal cursor movements as 
 * if it was printing to a terminal. Grid is positioned at starting position (3,1).
 * 
 */
void print_grid(Grid* g, FILE* f) {
    for(int i=1; i < g->length-1; i++) {
        fprintf(f, "\033[%d;3H", i+2);
        for(int j=1; j < g->length-1; j++) {
            char value = get_current_cell_value(g, i, j) & 0x01 ? '+' : '-';
            fprintf(f, "%c ", value);
        }
        fputc('\n', f);
    }
}

/**
 * Initialises the Grid g randomly. 
 * @random_alive_fraction: Integer in [0,100], the percentage probability of a grid
 *  cell to start alive.
 * 
 */
void set_random_state(Grid* g, int random_alive_fraction){
    for(int i=1; i < g->length-1; i++) {
        for(int j=1; j < g->length-1; j++) {
            set_current_cell_value(g, i, j, ((rand() % 100) < random_alive_fraction) & 0x01);
        }
    }
}