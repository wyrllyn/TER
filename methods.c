#include "methods.h"

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

void print_cost(m_data d) {
	printf(" cost 1 %d\ncost 2 %d\n   ", d.cost_1, d.cost_2);
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
			if (i != j)
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
			if (i != j)
				temp += mat[i][j] * sol[i];
		}
		(*row)[j] = temp;
	}
}

////// EVALUATION /////

// evaluation before adding solution 


// cost difference => delta
int delta_index(int** mat, int* row, int* col, int * sol, int index) {
	int del;
	if (sol[index] == 0)
		del = 1;
	else
		del = -1;
	return (del * (row[index] + col[index] + mat[index][index]));
}

int* calculate_costs(m_data d, int ** mat1, int ** mat2, int index) {
	int* temp = malloc(sizeof(int) * 2);
	temp[0] = d.cost_1 + delta_index(mat1, d.row_1, d.col_1, d.solution, index);
	temp[1] = d.cost_2 + delta_index(mat2, d.row_2, d.col_2, d.solution, index);
	return temp;
}

////// UPDATES ////////


// modification : TODO : something for delta
void update_row(int size, int ** row, int ** mat, int index, int delta) {
	for (int i = 0; i < size; i++) {
		if (index != i)
			(*row)[i] += mat[i][index] * delta;
	}
}

void update_col(int size, int** col, int ** mat, int index, int delta) {
	for (int j = 0; j < size; j++) {
		if (index != j)
			(*col)[j] += mat[index][j] * delta;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

first_s init(char* fileName) {
	first_s toReturn;

	// size + matrix
	if (parse(fileName, &toReturn.dat.size, &toReturn.mat1, &toReturn.mat2) == EXIT_FAILURE) {
		//return EXIT_FAILURE;
	}

	// solution
	generate_random_sol(&toReturn.dat.solution, toReturn.dat.size );
	for(int i = 0; i < toReturn.dat.size ; i++) {
		toReturn.dat.solution[i] = 0;
	}

	//costs
	toReturn.dat.cost_1 = init_cost(toReturn.mat1, toReturn.dat.size, toReturn.dat.solution);
	toReturn.dat.cost_2 = init_cost(toReturn.mat2, toReturn.dat.size, toReturn.dat.solution);
	//row and col
	init_row_value(&toReturn.dat.row_1, toReturn.mat1, toReturn.dat.size, toReturn.dat.solution);
	init_row_value(&toReturn.dat.row_2, toReturn.mat2, toReturn.dat.size, toReturn.dat.solution);
	init_col_value(&toReturn.dat.col_1, toReturn.mat1, toReturn.dat.size, toReturn.dat.solution);
	init_col_value(&toReturn.dat.col_2, toReturn.mat2, toReturn.dat.size, toReturn.dat.solution);

	return toReturn;
}