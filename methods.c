#include "methods.h"

// for each matrix

typedef struct matrix_data {
	// for both
	int * solution;
	// 1st matrix
	int cost_1;
	int * row_1;
	int* column_1;
	// 2nd matrix
	int cost_2;
	int * row_2;
	int* column_2;
	// matrix is always the same, don't put it here
} m_data;


// print methods ///////////////////////////////////////////////////
void print_mat(int ** mat, int size) {
	int i = 0;
	int j = 0;
	
	for (i = 0; i < size; i++){
		printf("\n");
		for (j = 0; j < size; j++){ //
			printf("%d ", mat[i][j]);
		}
	}
	printf("\n");
}

void print_tab(int* tab, int size) {
	for (int i = 0; i<size; i++) {
		printf("\n %d", tab[i]);
	}
	printf("\n");
}

////////////////   INIT METHODS///////////////////////////////////////////////////////////////

/// first solution used

void generate_random_sol(int ** tab, int size){
	int i = 0;
	*tab = malloc(sizeof(int) * size);
	for (i = 0; i < size; i++) {
		(*tab)[i] = rand() % 2;
	}
}

// Initial cost

/*
// debug
int init_cost_basic(int ** mat, int size, int* sol) {
	int tmp = 0;
	for (int i =0; i < size; i++) {
		for (int j = 0; j< size; j++) {
				tmp += sol[i]* sol[j]* mat[i][j];
		}
	}
	return tmp;
}

*/


int init_cost(int ** mat, int size, int* sol) {
	int tmp = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i; j++) {
			tmp += sol[i]*sol[j]*(mat[i][j]+ mat[j][i]);
		}
		tmp += sol[i] * mat[i][i];
	}
	return tmp;
}

// row and column values 

void init_row_value(int ** row, int ** mat, int size, int * sol) {
	(*row) = malloc(size*sizeof(int));
	int temp = 0;
	for (int i = 0; i < size ; i++) {
		temp = 0;
		for (int j =0; j < size; j++) {
			temp += mat[i][j] * sol[j];
		}
		(*row)[i] = temp;
	}

}

void init_col_value(int ** row, int ** mat, int size, int * sol) {
	(*row) = malloc(size*sizeof(int));
	int temp = 0;
	for (int j = 0; j < size ; j++) {
		temp = 0;
		for (int i =0; i < size; i++) {
			temp += mat[i][j] * sol[i];
		}
		(*row)[j] = temp;
	}
}

////// EVALUATION /////

// evaluation before adding solution ?


// cost difference => delta
int delta_index(int** mat, int* row, int* col, int * sol, int index) {
	int del;
	if (sol[index == 0])
		del = 1;
	else
		del = -1;
	printf("row index %d \n, col %d \n, mat val %d \n", row[index], col[index], mat[index][index]);

	return (del * (row[index] + col[index] + mat[index][index]));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

int init() {
	int nbMat = 0;
	int sizeMat = 0;	
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	char * testFileName = "res/test.dat";
	int ** mat1 = NULL;
	int ** mat2 = NULL;
	int * sol;

	if (parse(fileName, &sizeMat, &nbMat, &mat1, &mat2) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	generate_random_sol(&sol, sizeMat);
	return 0;
}