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

m_data * add_neigh(m_data * gSol, int gSize, m_data * neigh, int nSize);

void add_neigh_global (m_data ** gSol, int * gSize, m_data * neigh, int nSize);

m_data init_m_data(m_data d);

void free_mdata(m_data d);

int * copy(int const * sol, int size) ;

int* calculate_costs_global(int cost_1, int cost_2, int* row_1, int* row_2, int* col_1, int* col_2, int* solution, int ** mat1, int ** mat2, int index) ;


void generate_random_sol(int ** tab, int size);
void init_row_value(int ** row, int ** mat, int size, int * sol);
void init_col_value(int ** row, int ** mat, int size, int * sol);
int init_cost_basic(int ** mat, int size, int * sol);
int delta_index(int** mat, int* row, int* col, int * sol, int index);
int* calculate_costs(m_data d, int ** mat1, int ** mat2, int index);
int init_cost(int ** mat, int size, int* sol);

void update_col(int size, int** col, int ** mat, int index, int delta);
void update_row(int size, int ** row, int ** mat, int index, int delta);

int * calculate_row(int size, int * row, int** mat, int index, int delta);
int * calculate_col(int size, int * col, int** mat, int index, int delta);

int sameCost(int c1, int c2, int cc1, int cc2) ;

int * add(int* tab, int toadd, int size);

m_data * add_sol(m_data * solutions, m_data toAdd, int size);
m_data * remove_sol(m_data * solutions, int size, int * toRemove, int rmsize);

m_data * add_sol2(m_data * solutions, int size, int* costs, int* sol, int* row1, int* row2, int* col1, int* col2, int matsize );

m_data to_m_data(int index, m_data d, int* cost, int** mat1, int** mat2);


first_s init(char* fileName);
m_data * neighboorhood (m_data data, int** mat1, int** mat2, int * sizeSol, m_data* gSol, int sizeG);
void removeGlobal2(m_data * neigh, int sizeN, m_data** solutions, int * sizeSol);


void neighboorhood2 (m_data** solutions, m_data data, int** mat1, int** mat2, int * sizeSol, m_data* gSol, int sizeG);

m_data * neighboorhood3 (m_data data, int** mat1, int** mat2, int * sizeSol, m_data* gSol, int sizeG);

void neighboorhood4 (m_data** solutions, m_data data, int** mat1, int** mat2, int * sizeSol, m_data* gSol, int sizeG) ;

void free_matrix(int **matrix, int size_x);

void free_tab(m_data * d, int d_size, int size);

void globalNeigh ( int currentSol, int size, int ** mat1, int ** mat2, int* sizeSol, int *** sol, int*** rows1, int*** rows2, int*** cols1, int*** cols2, int** costs1, int**costs2 /* see for gsol & sizeG */);

#endif