#include "methods.h"

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

void generate_random_sol(int ** tab, int size){
	int i = 0;
	*tab = malloc(sizeof(int) * size);
	for (i = 0; i < size; i++) {
		(*tab)[i] = rand() % 2;
	}
}

void init_row_value(int ** row, int ** mat, int size, int * sol) {
	(*row) = malloc(size*sizeof(int));
	int temp = 0;
	for (int i = 0; i < size ; i++) {
		temp = 0;
		for (int j =0; j < i; j++) {
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
		for (int i =0; i < j; i++) {
			temp += mat[i][j] * sol[i];
		}
		(*row)[j] = temp;
	}
}

// evaluation before adding solution ?


// cost difference => delta
int delta_index(int** matrix, int* row, int* col, int * sol, int index) {
	int del;
	if (sol[index == 0])
		del = 1;
	else
		del = -1;

	return (del * (row[index] + col[index] + mat[index][index]));
}




// initial_cost => structure of 2 int ? => don't forget : 2 matrix not one

//// chose between this

void triang_mat(int *** mat, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i; j++){
			(*mat)[i][j] += (*mat)[j][i];
			(*mat)[j][i] = 0;
		}
	}
}

int init_cost_triang(int ** mat, int size, int* sol) {
	int tmp = 0;
	int val = 0;
	for (int i = 0; i < size; i++) {
		tmp = 0;
		for (int j = 0; j < i; j++) {
			tmp += sol[j] * mat[i][j];
		}
		tmp += mat[i][i];
		val += tmp * sol[i];
	}
	return val;
}


///////////// this
int init_cost_basic(int ** mat, int size, int* sol) {
	int tmp = 0;
	for (int i =0; i < size; i++) {
		for (int j = 0; j< size; j++) {
				tmp += sol[i]* sol[j]* mat[i][j];
		}
	}
	return tmp;
}


//// or this
int init_cost_basic_2(int ** mat, int size, int* sol) {
	int tmp = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i; j++) {
			tmp += sol[i]*sol[j]*(mat[i][j]+ mat[j][i]);
		}
		tmp += sol[i] * mat[i][i];
	}
	return tmp;
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