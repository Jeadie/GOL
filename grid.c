#include <stdio.h>
#include <stdlib.h>

#include "grid.h"


char get_grid_value(Grid* g, int x, int y);
char is_cell_alive(Grid* g, int x, int y);


Grid* init_grid(void) {
    Grid* g = (Grid*) malloc(sizeof(Grid));
    g->grid = (char*) malloc(LENGTH * LENGTH * sizeof(char));
    return g;
};


int get_number_of_live_neighbours(Grid* g, int x, int y){
    int count = 0;
    if (x != 0 && is_cell_alive(g,x-1, y)) {
        count ++;
    };
    if (y != 0 && is_cell_alive(g,x, y-1)) {
        count ++;
    };
    if (y != LENGTH && is_cell_alive(g,x, y+1)) {
        count ++;
    };
    if (x != LENGTH && is_cell_alive(g,x+1, y)) {
        count ++;
    };
    return count; 
}

char is_cell_alive(Grid* g, int x, int y) {
    return (char) get_grid_value(g, x, y) & 0x01;
}

char get_grid_value(Grid* g, int x, int y) {
    return g->grid[x*LENGTH + y];
}

void set_grid_value(Grid* g, int x, int y, char value) {
    g->grid[x*LENGTH + y] = value;
};

void update_cells(Grid* g) {
    for(int i=1; i < LENGTH-1; i++) {
            for(int j=1; j < LENGTH-1; j++) {
                set_grid_value(g, i, j, get_grid_value(g,i,j) >> 4);
            }
    }
}

void run_single_iteration(Grid* g) {
    for(int i=1; i < LENGTH-1; i++) {
        for(int j=1; j < LENGTH-1; j++) {
            char current_status = is_cell_alive(g, i, j);
            int live_neighbours = get_number_of_live_neighbours(g, i, j);
            char next_status = (current_status & (live_neighbours >= 2)) || (!current_status & (live_neighbours == 3));
            set_grid_value(g, i, j, current_status | (next_status << 4));
        }
    }
    update_cells(g);
}

char* get_current_grid(Grid* g) {
    return g->grid;
}; 

void delete_grid(Grid* g){
    free(g->grid);
    free(g);
};

void print_grid(Grid* g, FILE* f) {
    for(int i=1; i < LENGTH-1; i++) {
        for(int j=1; j < LENGTH-1; j++) {
            char value = get_grid_value(g, i, j) & 0x01 ? 'X' : 'O';
            fputc(value, f);
        }
        fputc('\n', f);
    }
}

void set_random_state(Grid* g){
    for(int i=1; i < LENGTH-1; i++) {
        for(int j=1; j < LENGTH-1; j++) {
            set_grid_value(g, i, j, rand() & 0x01);
        }
    }
};