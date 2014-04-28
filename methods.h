#ifndef METHODS_H
#define METHODS_H

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

typedef struct matrix_data {
	// for both
	int size;
	int * solution;
	// 1st matrix
	int cost_1;
	int * row_1;
	int* col_1;
	// 2nd matrix
	int cost_2;
	int * row_2;
	int* col_2;
	// matrix is always the same, don't put it here
} m_data;

typedef struct first_sol {
	int ** mat1;
	int ** mat2;
	m_data dat;
} first_s;


void print_mat(int ** mat, int size);
void print_tab(int* tab, int size);
void print_cost(m_data d);
void generate_random_sol(int ** tab, int size);
void init_row_value(int ** row, int ** mat, int size, int * sol);
void init_col_value(int ** row, int ** mat, int size, int * sol);
int init_cost_basic(int ** mat, int size, int * sol);
int delta_index(int** mat, int* row, int* col, int * sol, int index);
int init_cost(int ** mat, int size, int* sol);

void update_col(int size, int** col, int ** mat, int index, int delta);
void update_row(int size, int ** row, int ** mat, int index, int delta);
first_s init(char* fileName);
//generate neighboors

#endif