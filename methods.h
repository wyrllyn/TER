#ifndef METHODS_H
#define METHODS_H

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"



void print_mat(int ** mat, int size);
void print_tab(int* tab, int size);
void generate_random_sol(int ** tab, int size);
void init_row_value(int ** row, int ** mat, int size, int * sol);
void init_col_value(int ** row, int ** mat, int size, int * sol);
int init_cost_basic(int ** mat, int size, int * sol);
int delta_index(int** mat, int* row, int* col, int * sol, int index);
int init_cost(int ** mat, int size, int* sol);

int init();
//generate neighboors

#endif