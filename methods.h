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

int global(char* fileName);


void print_mat(int ** mat, int size);
void print_tab(int* tab, int size);
void print_cost(m_data d);

void addInt(int ** tab, int toadd, int size);

int isInto(int j, int* toRem, int rmsize);

int isTheSame (int * first, int * second, int size);


int * copy(int const * sol, int size) ;

int* calculate_costs_global(int cost_1, int cost_2, int* row_1, int* row_2, int* col_1, int* col_2, int* solution, int ** mat1, int ** mat2, int index) ;


void generate_random_sol(int ** tab, int size);
void init_row_value(int ** row, int ** mat, int size, int * sol);
void init_col_value(int ** row, int ** mat, int size, int * sol);
int init_cost_basic(int ** mat, int size, int * sol);
int delta_index(int** mat, int* row, int* col, int * sol, int index);
int init_cost(int ** mat, int size, int* sol);

int sameCost(int c1, int c2, int cc1, int cc2) ;

int * add(int* tab, int toadd, int size);



first_s init(char* fileName);

//void removeGlobal2(m_data * neigh, int sizeN, m_data** solutions, int * sizeSol);


void free_matrix(int **matrix, int size_x);

void free_tab(m_data * d, int d_size, int size);

void globalNeigh ( int currentSol, int size, int ** mat1, int ** mat2, int* sizeSol, int *** sol, int*** rows1, int*** rows2, int*** cols1, int*** cols2, int** costs1, int**costs2 /* see for gsol & sizeG */);

void write_res(int * costs1, int * costs2, int size);

#endif