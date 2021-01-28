#include <stdio.h>
#include <stdlib.h>

#include "grid.h"


char get_grid_value(Grid* g, int x, int y);
char is_cell_alive(Grid* g, int x, int y);

/**
 * Initialises the Grid struct.
 * 
 */
Grid* init_grid(int length) {
    Grid* g = (Grid*) malloc(sizeof(Grid));
    g->grid = (char*) malloc(length * length * sizeof(char));
    g->length = length;
    return g;
};

/**
 * Gets the number of alive neighbours for a given cell. 
 * 
 */
int get_number_of_live_neighbours(Grid* g, int x, int y){
    int count = 0;
    if (x != 0 && is_cell_alive(g,x-1, y)) {
        count ++;
    };
    if (y != 0 && is_cell_alive(g,x, y-1)) {
        count ++;
    };
    if (y != g->length && is_cell_alive(g,x, y+1)) {
        count ++;
    };
    if (x != g->length && is_cell_alive(g,x+1, y)) {
        count ++;
    };
    return count; 
}

/**
 *  Returns 0x01 if the Grid at position (x,y) is alive, 0x00 otherwise.
 * 
 */
char is_cell_alive(Grid* g, int x, int y) {
    return (char) get_grid_value(g, x, y) & 0x01;
}

/**
 * Returns the value of the Grid at (x,y).
 */
char get_grid_value(Grid* g, int x, int y) {
    return g->grid[x*g->length + y];
}

/**
 * Sets the value of the Grid at (x,y). Not responsible for properly setting the 
 * current and upcoming values appropriately. 
 */
void set_grid_value(Grid* g, int x, int y, char value) {
    g->grid[x*g->length + y] = value;
};

/**
 * Updates all cells in the Grid g by setting the current value of each cell to its 
 * current next value. Does not clear the next value of any cell (the 4 leftmost 
 * bits).
 *
 */
void update_cells(Grid* g) {
    for(int i=1; i < g->length-1; i++) {
            for(int j=1; j < g->length-1; j++) {
                set_grid_value(g, i, j, get_grid_value(g,i,j) >> 4);
            }
    }
}

/**
 * Runs a single iteration of Game of Life.
 */
void run_single_iteration(Grid* g) {
    for(int i=1; i < g->length-1; i++) {
        for(int j=1; j < g->length-1; j++) {
            char current_status = is_cell_alive(g, i, j);
            int live_neighbours = get_number_of_live_neighbours(g, i, j);
            char next_status = (current_status & (live_neighbours == 2 || live_neighbours == 3)) || (!current_status & (live_neighbours == 3));

            // Sets grid cell so that next status is at the 4 leftmost bits.
            set_grid_value(g, i, j, current_status | (next_status << 4));
        }
    }
    update_cells(g);
}

/**
 * Deletes the Grid struct and all associated memory.  
 * 
 */
void delete_grid(Grid* g){
    free(g->grid);
    free(g);
};


/**
 * Prints the grid to the file. Function prints grid with terminal cursor movements as 
 * if it was printing to a terminal. Grid is positioned at starting position (3,1).
 * 
 */
void print_grid(Grid* g, FILE* f) {
    for(int i=1; i < g->length-1; i++) {
        fprintf(f, "\033[%d;3H", i+2);
        for(int j=1; j < g->length-1; j++) {
            char value = get_grid_value(g, i, j) & 0x01 ? '+' : '-';
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
            set_grid_value(g, i, j, ((rand() % 100) < random_alive_fraction) & 0x01);
        }
    }
};