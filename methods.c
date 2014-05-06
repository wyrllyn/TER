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
	printf("cost 1 %d\ncost 2 %d\n   ", d.cost_1, d.cost_2);
}




//// to move later -- add and remove solutions ////

// return 0 if false, 1 if true
int isInto(int j, int* toRem, int rmsize) {
	for (int i = 0; i < rmsize; i++) {
		if (toRem[i] == j)
			return 1;
	}
	return 0;
}



int * add(int* tab, int toadd, int size) {
	int * tmp = malloc(sizeof(int) * size);

	for (int i = 0; i < size - 1; i++) {
		tmp[i] = tab[i];
	}

	tmp[size - 1] = toadd;
	return tmp;
}

m_data * add_sol(m_data * solutions, m_data toAdd, int size) {
	m_data * tmp = malloc(sizeof(m_data) * size);

	for (int i  = 0; i < size - 1; i++) {
		tmp[i] = solutions[i];
	}
	tmp[size - 1] = toAdd;
	return tmp;
}



m_data * add_neigh(m_data * gSol, int gSize, m_data * neigh, int nSize) {
	m_data * tmp = malloc(sizeof(m_data) * (gSize + nSize));
	for (int i = 0; i < gSize; i++) {
		tmp[i] = gSol[i];
	}
	for (int i = 0; i < nSize; i++) {
		tmp[i + gSize] = neigh[i];
	}
	free(gSol);
	return tmp;
}

void add_neigh_global (m_data ** gSol, int * gSize, m_data * neigh, int nSize) {
	(*gSol)= malloc(sizeof(m_data) * ((*gSize) + nSize));
	for (int i = 0; i < (*gSize); i++) {
		(*gSol)[i] = (*gSol)[i];
	}	
	for (int i = 0; i < nSize; i++) {
		(*gSol)[i+(*gSize)] = neigh[i];
	}

	(*gSize) += nSize;
}


m_data * remove_sol(m_data * solutions, int size, int * toRemove, int rmsize) {
	m_data * tmp = malloc(sizeof(m_data) * (size - rmsize));
	int a = 0;

	for (int i = 0; i < size - rmsize; i++) {
		for (int j = 0; j < rmsize ;j++) {
			if (isInto(a, toRemove, rmsize) == 1) {
				a++;
			}
		}
		tmp[i] = solutions[a];
		a++;
	}
	return tmp;
}

m_data to_m_data(int index, m_data d, int* cost, int** mat1, int** mat2) {
	m_data tmp;
	int delta = 1;

	tmp.size = d.size;
	tmp.cost_1 = cost[0];
	tmp.cost_2 = cost[1];

	tmp.solution = malloc(sizeof(int) * tmp.size);
	for (int i = 0; i < tmp.size; i++)
		tmp.solution[i] = d.solution[i];

	if (tmp.solution[index] == 0 ) {
		tmp.solution[index] = 1;
		delta = 1;
	}
	else {
		tmp.solution[index] = 0;
		delta = -1;
	}

	tmp.row_1 = calculate_row(tmp.size, d.row_1, mat1, index, delta);
	tmp.row_2 = calculate_row(tmp.size, d.row_2, mat2, index, delta);

	tmp.col_1 = calculate_col(tmp.size, d.col_1, mat1, index, delta);
	tmp.col_2 = calculate_col(tmp.size, d.col_2, mat2, index, delta);

	return tmp;

}

m_data init_m_data(m_data d) {
	m_data tmp;

	tmp.size = d.size;
	tmp.cost_1 =  d.cost_1;
	tmp.cost_2 = d.cost_2;

	tmp.solution = malloc(sizeof(int) * tmp.size);
	for (int i = 0; i < tmp.size; i++)
		tmp.solution[i] = d.solution[i];
	tmp.row_1 = malloc(sizeof(int) * tmp.size);
	tmp.row_2 = malloc(sizeof(int) * tmp.size);
	tmp.col_1 = malloc(sizeof(int) * tmp.size);
	tmp.col_2 = malloc(sizeof(int) * tmp.size);

	for (int i = 0; i < tmp.size; i++) {
		tmp.row_1 [i] = d.row_1[i];
		tmp.row_2 [i] = d.row_2[i];
		tmp.col_1 [i] = d.col_1[i];
		tmp.col_2 [i] = d.col_2[i];
	}

	return tmp;
}


/// COMPARE

//return 0 if false, 1 if true
int isTheSame (int * first, int * second, int size) {
	for (int i = 0; i < size; i++) {
		if (first[i] != second[i])
			return 0;
	}
	return 1;
}

int * copy(int * sol, int size) {
	int * tmp = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		tmp[i] = sol[i];
	}

	return tmp;
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
	// print_tab(d.row_2, 5);
	temp[0] = d.cost_1 + delta_index(mat1, d.row_1, d.col_1, d.solution, index);
	temp[1] = d.cost_2 + delta_index(mat2, d.row_2, d.col_2, d.solution, index);
	return temp;
}

////// UPDATES ////////


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

int * calculate_row(int size, int * row, int** mat, int index, int delta) {
	int * tmp = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		if (index != i)
			tmp[i] = mat[i][index] * delta + row[i];
		else tmp[i] = 0;
	}
	return tmp;
}

int * calculate_col(int size, int * col, int** mat, int index, int delta) {
	int * tmp = malloc(sizeof(int) * size);
	for (int j = 0; j < size; j++) {
		if (index != j)
			tmp[j] = mat[index][j] * delta + col[j];
		else tmp[j] = 0;
	}
	return tmp;
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

	//to remove
/*	for(int i = 0; i < toReturn.dat.size ; i++) {
		toReturn.dat.solution[i] = 0;
	}
	toReturn.dat.solution[0] = 1; */

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


m_data * neighboorhood (m_data data, int** mat1, int** mat2, int * sizeSol, m_data* gSol, int sizeG) {

	int * tmp;

	m_data data_tmp;
	m_data * solutions;


// adds solutions
	for (int i = 0; i < data.size; i++) {
		tmp = calculate_costs(data, mat1, mat2, i);
		if (tmp[0] >= data.cost_1 || tmp[1] >= data.cost_2) {
			data_tmp = to_m_data(i, data, tmp, mat1, mat2);
			(*sizeSol)++;
			solutions = add_sol(solutions, data_tmp, (*sizeSol));
		}
	}
	free(tmp);
/*	for (int i = 0; i < (*sizeSol); i++) {
		printf("index i = %d \n", i);
//		print_tab(solutions[i].solution, solutions[i].size);
		//print_tab(solutions[i].row_1, solutions[i].size);
		print_cost(solutions[i]);
	}
	*/

	int rmsize = 0;
	int * toRem;

	for (int i = 0; i < (*sizeSol); i++) {
		for (int j = i+1; j < (*sizeSol); j++) {
			if((solutions[i].cost_1 > solutions[j].cost_1 && solutions[i].cost_2 > solutions[j].cost_2) && (isInto(j, toRem, rmsize) == 0)){
				rmsize++;
				toRem = add(toRem, j, rmsize);
			}
			else if ((solutions[i].cost_1 < solutions[j].cost_1 && solutions[i].cost_2 < solutions[j].cost_2) &&  (isInto(i, toRem, rmsize) == 0)) {
				rmsize++;
				toRem = add(toRem, i, rmsize);
				break;
			} 
		}
	}
//	print_tab(toRem, rmsize);

	solutions = remove_sol(solutions,(*sizeSol), toRem, rmsize);
	(*sizeSol) -= rmsize;

	rmsize = 0;
	toRem = NULL;

	for (int i = 0; i < (*sizeSol); i++) {
		for (int j = 0; j < sizeG; j++) {
			if ((isInto(i, toRem, rmsize) == 0) ) {
				if (isTheSame(solutions[i].solution, gSol[j].solution, data.size) == 1) {
					rmsize++;
					toRem = add(toRem, i, rmsize);
				}
			}
		}
	}

	solutions = remove_sol(solutions,(*sizeSol), toRem, rmsize);
	(*sizeSol) -= rmsize;

	free(toRem);

	return solutions;
}

// removes from sol

void removeGlobal(m_data * neigh, int sizeN, m_data** sol, int * sizeSol) {
	int* toRem;
	int rmsize = 0;
	// i neigh - j sol
	for (int j = 0; j < (*sizeSol); j++) { 
		for (int i = 0; i < sizeN; i++) {
			if ((neigh[i].cost_1 > (*sol)[j].cost_1 && neigh[i].cost_2 > (*sol)[j].cost_2) && (isInto(j, toRem, rmsize) == 0)) {
				rmsize++;
				toRem = add (toRem, j, rmsize);
			}
		}
	}

	(*sol) = remove_sol((*sol), (*sizeSol), toRem, rmsize);
	(*sizeSol) -= rmsize;
}

void removeGlobal2(m_data * neigh, int sizeN, m_data** solutions, int * sizeSol) {
	int rmsize = 0;
	int * toRem;

	(*solutions) = add_neigh((*solutions), (*sizeSol), neigh, sizeN);
	(*sizeSol) += sizeN;
	for (int i = 0; i < (*sizeSol); i++) {
		for (int j = i+1; j < (*sizeSol); j++) {
			if(((*solutions)[i].cost_1 > (*solutions)[j].cost_1 && (*solutions)[i].cost_2 > (*solutions)[j].cost_2) && (isInto(j, toRem, rmsize) == 0)){
				rmsize++;
				toRem = add(toRem, j, rmsize);
			}
			else if (((*solutions)[i].cost_1 < (*solutions)[j].cost_1 && (*solutions)[i].cost_2 < (*solutions)[j].cost_2) &&  (isInto(i, toRem, rmsize) == 0)) {
				rmsize++;
				toRem = add(toRem, i, rmsize);
				break;
			} 
		}
	}

	(*solutions) = remove_sol((*solutions),(*sizeSol), toRem, rmsize);
	(*sizeSol) -= rmsize;
}

/// free


void free_matrix(int **matrix, int size_x)
{
    for(int i = 0; i < size_x; i++)
        free(matrix[i]);
    free(matrix);
}
void free_mdata(m_data d) {
	free(d.solution);
	free(d.row_1);
	free(d.row_2);
	free(d.col_1);
	free(d.col_2);
}