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

//////////////////////////////////////////////////////////////////////////////


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
	int * tmp = (int*)malloc(sizeof(int) * size);

	for (int i = 0; i < size - 1; i++) {
		tmp[i] = tab[i];
	}

	tmp[size - 1] = toadd;
	if (tab != NULL)
		free(tab);
	return tmp;
}

void addInt(int ** tab, int toadd, int size) {
	int * tmp = malloc(sizeof(int) * size);
	for (int i = 0; i < size - 1; i++) {
		tmp[i] = (*tab) [i];
	}

	*tab = NULL;

	tmp[size - 1] = toadd;
	(*tab) = (int*) malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		(*tab) [i] = tmp[i];
	}

	free(tmp);
}


m_data * add_sol(m_data * solutions, m_data toAdd, int size) {
	m_data * tmp = (m_data *) malloc(sizeof(m_data) * size);

	for (int i  = 0; i < size - 1; i++) {
		tmp[i] = solutions[i];
	}
	tmp[size - 1] = toAdd;
	if (solutions != NULL)
		free(solutions);

	return tmp;
}


m_data to_m_data(int index, m_data d, int* cost, int** mat1, int** mat2) {
	m_data tmp;
	int delta = 1;

	tmp.size = d.size;
	tmp.cost_1 = cost[0];
	tmp.cost_2 = cost[1];

	tmp.solution = (int*)malloc(sizeof(int) * tmp.size);
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

m_data * add_sol2(m_data * solutions, int size, int* costs, int* sol, int* row1, int* row2, int* col1, int* col2, int matsize ) {
	m_data * tmp = (m_data *) malloc(sizeof(m_data) * size);

	for (int i  = 0; i < size - 1; i++) {
		tmp[i] = solutions[i];
	}
	tmp[size - 1].cost_1 = costs[0];
	tmp[size - 1].cost_2 = costs[1];

	tmp[size - 1].size = matsize;

	tmp[size - 1].row_1 = malloc(sizeof(int)* matsize);
	tmp[size - 1].row_2 = malloc(sizeof(int)* matsize);

	tmp[size - 1].col_1 = malloc(sizeof(int)* matsize);
	tmp[size - 1].col_2 = malloc(sizeof(int)* matsize);
	tmp[size - 1].solution = malloc(sizeof(int)* matsize);

	for (int i = 0; i < matsize; i++) {
		tmp[size - 1].row_1[i] = row1[i];
		tmp[size - 1].row_2[i] = row2[i];
		tmp[size - 1].col_1[i] = col1[i];
		tmp[size - 1].col_2[i] = col2[i];
		tmp[size - 1].solution[i] = sol[i];
	}


	if (solutions != NULL) {
		/*for (int i = 0; i < size - 1; i++) {
			free(solutions[i].solution);
			solutions[i].solution = NULL;
			free(solutions[i].row_1);
			solutions[i].row_1 = NULL;
		}*/
		free(solutions);
		solutions = NULL;
	}


	return tmp;

}



m_data * add_neigh(m_data * gSol, int gSize, m_data * neigh, int nSize) {
	m_data * tmp = (m_data *)malloc(sizeof(m_data) * (gSize + nSize));
	for (int i = 0; i < gSize; i++) {
		tmp[i] = gSol[i];
	}
	for (int i = 0; i < nSize; i++) {
		tmp[i + gSize] = neigh[i];
	}
	if (gSol != NULL)
		free(gSol);
	return tmp;
}

void add_neigh2(m_data ** gSol, int gSize, m_data * neigh, int nSize) {
	for (int i = 0; i < nSize; i++) {
		(*gSol)[i + gSize] = neigh[i];
	}
}

void add_neigh_global (m_data ** gSol, int * gSize, m_data * neigh, int nSize) {
	(*gSol)=(m_data *) malloc(sizeof(m_data) * ((*gSize) + nSize));
	for (int i = 0; i < (*gSize); i++) {
		(*gSol)[i] = (*gSol)[i];
	}	
	for (int i = 0; i < nSize; i++) {
		(*gSol)[i+(*gSize)] = neigh[i];
	}

	(*gSize) += nSize;
}


m_data * remove_sol(m_data * solutions, int size, int * toRemove, int rmsize) {
	m_data * tmp = (m_data *) malloc(sizeof(m_data) * (size - rmsize));
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
	if (solutions != NULL && size > 0) {
	/*	for (int i = 0; i < size; i++) {
			free(solutions[i].solution);
			free(solutions[i].row_1);
			free(solutions[i].row_2);
			free(solutions[i].col_1);
			free(solutions[i].col_2);
		}*/
		free(solutions);
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

int sameCost(int c1, int c2, int cc1, int cc2) {
	if (c1 == cc1 && c2 == cc2)
		return 1;
	else
		return 2;
}

int * copy(int const * sol, int size) {
	int * tmp = (int*)malloc(sizeof(int) * size);
	memcpy(tmp, sol, size * sizeof(int));

	return tmp;
}


////////////////   INIT METHODS///////////////////////////////////////////////////////////////

/// first solution used

void generate_random_sol(int ** tab, int size){
	int i = 0;
	*tab = (int*)malloc(sizeof(int) * size);
	for (i = 0; i < size; i++) {
		(*tab)[i] = rand() % 2;
	}
}

// Initial cost


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
	(*row) = (int*)malloc(size*sizeof(int));
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
	(*row) = (int*)malloc(size*sizeof(int));
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
	int* temp = (int*)malloc(sizeof(int) * 2);
	// print_tab(d.row_2, 5);
	temp[0] = d.cost_1 + delta_index(mat1, d.row_1, d.col_1, d.solution, index);
	temp[1] = d.cost_2 + delta_index(mat2, d.row_2, d.col_2, d.solution, index);
	return temp;
}

int* calculate_costs_global(int cost_1, int cost_2, int* row_1, int* row_2, int* col_1, int* col_2, int* solution, int ** mat1, int ** mat2, int index) {
	int* temp = (int*)malloc(sizeof(int) * 2);
	// print_tab(d.row_2, 5);
	temp[0] = cost_1 + delta_index(mat1, row_1, col_1, solution, index);
	temp[1] = cost_2 + delta_index(mat2, row_2, col_2, solution, index);
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

// OK
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

int global(char* fileName) {

/////////////// INIT////////////////////
////////////////////////////////////////
	first_s solu;
	int max = 10000;

	// size + matrix
	if (parse(fileName, &solu.dat.size, &solu.mat1, &solu.mat2) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	// solution
	generate_random_sol(&solu.dat.solution, solu.dat.size );

	//costs
	solu.dat.cost_1 = init_cost(solu.mat1, solu.dat.size, solu.dat.solution);
	solu.dat.cost_2 = init_cost(solu.mat2, solu.dat.size, solu.dat.solution);
	//row and col
	init_row_value(&solu.dat.row_1, solu.mat1, solu.dat.size, solu.dat.solution);
	init_row_value(&solu.dat.row_2, solu.mat2, solu.dat.size, solu.dat.solution);
	init_col_value(&solu.dat.col_1, solu.mat1, solu.dat.size, solu.dat.solution);
	init_col_value(&solu.dat.col_2, solu.mat2, solu.dat.size, solu.dat.solution);


	int sizeSol = 0;

	int ** solutions = (int**)malloc(sizeof(int*) * max);
	int ** rows1 = (int**)malloc(sizeof(int*) * max);
	int ** rows2 = (int**)malloc(sizeof(int*) * max);
	int ** cols1 = (int**)malloc(sizeof(int*) * max);
	int ** cols2 = (int**)malloc(sizeof(int*) * max);
	int* costs1 = (int*)malloc(sizeof(int) * max);
	int* costs2 = (int*)malloc(sizeof(int) * max);
	for (int i = 0; i < max; i++) {
		solutions[i] = malloc(sizeof(int) * solu.dat.size);
		rows1[i] = malloc(sizeof(int) * solu.dat.size);
		rows2[i] = malloc(sizeof(int) * solu.dat.size);
		cols1[i] = malloc(sizeof(int) * solu.dat.size);
		cols2[i] = malloc(sizeof(int) * solu.dat.size);
	}

	/// add init sol /////
	//////////////////////

	for (int i = 0; i < solu.dat.size; i++) {
		solutions[0][i] = solu.dat.solution[i];
		rows1 [0][i] = solu.dat.row_1[i];
		rows2 [0][i] = solu.dat.row_2[i];
		cols1 [0][i] = solu.dat.col_1[i];
		cols2 [0][i] = solu.dat.col_2[i];
	}
	costs1[0] = solu.dat.cost_1;
	costs2[0] = solu.dat.cost_2;

	sizeSol++;

	///// Global loop ////////////
	//////////////////////////////


	

	int number = 0;
	int oldSol = 0;

	int * oldCost = malloc(sizeof(int) * 2);



	while (number <  30) {
		printf("number =  %d \n", number);

		oldSol = sizeSol;
		if (sizeSol > 0) {
			oldCost[0] = costs1[sizeSol - 1];
			oldCost[1] = costs2[sizeSol - 1];
		}

		for (int i = 0; i < sizeSol; i++) {
			globalNeigh (i, solu.dat.size, solu.mat1, solu.mat2, &sizeSol, &solutions, &rows1, &rows2, &cols1, &cols2, &costs1, &costs2 /* see for gsol & sizeG */);
		}
	/*
		for (int i = 0; i < sizeSol; i++) {		
			sizeN = 0;		
			neigh = neighboorhood3 (solutions[i], solu.mat1, solu.mat2, &sizeN, solutions, sizeSol);

			removeGlobal2(neigh, sizeN, &solutions, &sizeSol);
		}
	*/	

		if (oldSol - sizeSol == 0) {
			if (sameCost (oldCost[0], oldCost[1], costs1[sizeSol - 1], costs2[sizeSol - 1] ) == 1)
				break;
		}

		number++;
	}

	free(oldCost);

	////////////////// VERIFICATION /////////////////////////
	////////////////////////////////////////////////////////
	for (int i = 0; i < sizeSol; i++) {
		printf("index i = %d\ncosts : %d | %d \n",i, costs1[i], costs2[i] );
		printf("costs with init : %d | %d\n",init_cost(solu.mat1, solu.dat.size, solutions[i]), init_cost(solu.mat2, solu.dat.size, solutions[i]) );
	}



/////////////////////////FREE////////////////////////////
////////////////////////////////////////////////////////
	free_matrix(solutions, max);
	free_matrix(rows1,  max);
	free_matrix(rows2,  max);
	free_matrix(cols1,  max);
	free_matrix(cols2,  max);
	free(costs1);
	free(costs2);
	free_matrix(solu.mat1, solu.dat.size);
	free_matrix(solu.mat2, solu.dat.size);
	free(solu.dat.row_1);
	free(solu.dat.row_2);
	free(solu.dat.col_2);
	free(solu.dat.col_1);
	free(solu.dat.solution);

	return EXIT_SUCCESS;

}

void globalNeigh ( int currentSol, int size, int ** mat1, int ** mat2, int* sizeSol, int *** sol, int*** rows1, int*** rows2, int*** cols1, int*** cols2, int** costs1, int**costs2 /* see for gsol & sizeG */) {
	///////////// ADDS EVERY SOLUTION WITH AN EQUIVALENT OR BETTER COST ///////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	// TODO : if with maximal size ...

	int * tmp = NULL;
	for (int i = 0; i < size; i++) {
		tmp = calculate_costs_global((*costs1)[currentSol], (*costs2)[currentSol], (*rows1)[currentSol], (*rows2)[currentSol], (*cols1)[currentSol],
		(*cols2)[currentSol], (*sol)[currentSol], mat1, mat2, i);

		if(tmp[0] >= (*costs1)[currentSol] || tmp[1] >= (*costs2)[currentSol]) {
			int delta = 1;

			// fill
			/*printf("first \n");
			print_tab((*sol)[currentSol], size);*/
			for (int j = 0; j < size; j++) {
				(*sol)[(*sizeSol)][j] = (*sol)[currentSol][j];
				(*rows1)[(*sizeSol)][j] = (*rows1)[currentSol][j];
				(*rows2)[(*sizeSol)][j] = (*rows2)[currentSol][j];
				(*cols1)[(*sizeSol)][j] = (*cols1)[currentSol][j];
				(*cols2)[(*sizeSol)][j] = (*cols2)[currentSol][j];
			}
			(*costs1)[(*sizeSol)] = tmp[0];
			(*costs2) [(*sizeSol)] = tmp[1];

		/*	printf("second\n");
			print_tab((*sol)[(*sizeSol)], size);*/
			// delta
			if ((*sol)[(*sizeSol)][i] == 0 ) {
				(*sol)[(*sizeSol)][i] = 1;
				delta = 1;
			}
			else {
				(*sol)[(*sizeSol)][i] = 0;
				delta = -1;
			}

			/*printf("third\n");
			print_tab((*sol)[(*sizeSol)], size);*/

			// update cols and rows 
			for (int k = 0; k < size; k++) {
				if (i != k) {
					(*cols1)[(*sizeSol)][k] += mat1[i][k] * delta;
					(*cols2)[(*sizeSol)][k] += mat2[i][k] * delta;
					(*rows1)[(*sizeSol)][k] += mat1[k][i] * delta;
					(*rows2)[(*sizeSol)][k] += mat2[k][i] * delta;
				}
			}
			(*sizeSol)++;
		}
		free(tmp);
	}


	//// REMOVE /////

	int rmsize = 0;
	int * toRem = malloc(sizeof(int) * 10000);

	for (int i = 0; i < (*sizeSol); i++) {
		for (int j = i +1; j < (*sizeSol); j++) {
			if((*costs1)[i] >= (*costs1)[j] && (*costs2)[i] >= (*costs2)[j] && (isInto(j, toRem, rmsize) == 0)) {
				toRem[rmsize] = j;
				rmsize++;
			}
			else if ((*costs1)[i] <= (*costs1)[j] && (*costs2)[i] <= (*costs2)[j]&& (isInto(i, toRem, rmsize) == 0)) {
				toRem[rmsize] = i;
				rmsize++;
			}
		}
	}

/*	for (int i = 0; i < (*sizeSol); i++) {
		printf("index i = %d\ncosts : %d | %d \n",i, (*costs1)[i], (*costs2)[i] );
	}

	print_tab(toRem, rmsize);*/

	
	int a = 0;
	for (int i = 0; i < (*sizeSol) - rmsize; i++) {
		for (int j = 0; j < rmsize ;j++) {
			if (isInto(a, toRem, rmsize) == 1) {
			//	printf("%d remove \n ", a);
				a++;
			}
		}
		if (i != a) {
			(*costs1)[i] = (*costs1)[a];
			(*costs2)[i] = (*costs2)[a];
			for (int k = 0; k < size;k++) {
				(*sol)[i][k] = (*sol)[a][k];
				(*rows1)[i][k] = (*rows1)[a][k];
				(*rows2)[i][k] = (*rows2)[a][k];
				(*cols1)[i][k] = (*cols1)[a][k];
				(*cols2)[i][k] = (*cols2)[a][k];
			}
		}
		a++;
	}

	(*sizeSol) -= rmsize;

	if (toRem !=NULL)
		free(toRem);

	
}




m_data * neighboorhood3 (m_data data, int** mat1, int** mat2, int * sizeSol, m_data* gSol, int sizeG) {

	int * tmp = NULL;
	m_data * solutions = malloc(sizeof(m_data) * data.size);

	int * dsol;
	int * drow1;
	int * drow2;
	int * dcol1;
	int * dcol2;

// adds solutions
	for (int i = 0; i < data.size; i++) {
		tmp = calculate_costs(data, mat1, mat2, i);
		if (tmp[0] >= data.cost_1 || tmp[1] >= data.cost_2) {

			int delta = 1;			

			dsol = (int*)malloc(sizeof(int) * data.size);
			for (int j = 0; j < data.size; j++)
				dsol[j] = data.solution[j];

			if (dsol[i] == 0 ) {
				dsol[i] = 1;
				delta = 1;
			}
			else {
				dsol[i] = 0;
				delta = -1;
			}


			drow1 = copy(data.row_1, data.size);
			update_row(data.size, &drow1, mat1, i, delta);

			drow2 = copy(data.row_2, data.size);
			update_row(data.size, &drow2, mat2, i, delta);
			
			dcol1 = copy(data.col_1, data.size);
			update_col(data.size, &dcol1, mat1, i, delta);

			dcol2 = copy(data.col_2, data.size);
			update_col(data.size, &dcol2, mat2, i, delta);

			(*sizeSol)++;

		//	solutions = add_sol2(solutions, (*sizeSol), tmp, dsol, drow1, drow2, dcol1, dcol2, data.size );

			if (*sizeSol <= data.size) {
				solutions[(*sizeSol) -1].cost_1 = tmp[0];
				solutions[(*sizeSol) -1].cost_2 = tmp[1];
				solutions[(*sizeSol) -1].size = data.size;

				solutions[(*sizeSol) -1].row_1 = malloc(sizeof(int) * data.size);

				solutions[(*sizeSol) -1].row_2 = malloc(sizeof(int) * data.size);
				solutions[(*sizeSol) -1].col_1 = malloc(sizeof(int) * data.size);
				solutions[(*sizeSol) -1].col_2 = malloc(sizeof(int) * data.size);
				solutions[(*sizeSol) -1].solution = malloc(sizeof(int) * data.size);

				for (int i = 0; i < data.size; i++) {
					solutions[(*sizeSol) -1].row_1[i] = drow1[i];
					solutions[(*sizeSol) -1].row_2[i] = drow2[i];
					solutions[(*sizeSol) -1].col_1[i] = dcol1[i];
					solutions[(*sizeSol) -1].col_2[i] = dcol2[i];
					solutions[(*sizeSol) -1].solution[i] = dsol[i];
				}

			}
			else {
				printf("size Error \n");
			}

			if (dsol != NULL) {
				free(dsol);
				dsol = NULL;
			}
			if (dcol1 != NULL)
				free(dcol1);
			if (dcol2 != NULL)
				free(dcol2);
			if (drow1 != NULL)
				free(drow1);
			if (drow2 != NULL)
				free(drow2);
		}
		free(tmp);
	}


	int rmsize = 0;
	int * toRem = NULL;

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
		for (int j = 0; j < sizeG; j++) {
			if ((isInto(i, toRem, rmsize) == 0) ) {
				if (sameCost(solutions[i].cost_1, solutions[i].cost_2, gSol[j].cost_1, gSol[j].cost_2) == 1) {
					rmsize++;
					toRem = add(toRem, i, rmsize);
				}
			}
		}
	}

//	print_tab(toRem, rmsize);
	//solutions = remove_sol(solutions,(*sizeSol), toRem, rmsize);


	int a = 0;
	for (int i = 0; i < (*sizeSol) - rmsize; i++) {
		for (int j = 0; j < rmsize ;j++) {
			if (isInto(a, toRem, rmsize) == 1) {
			//	printf("%d remove \n ", a);
				a++;
			}
		}
		if (i != a) {
			solutions[i].cost_1 = solutions[a].cost_1;
			solutions[i].cost_2 = solutions[a].cost_2;
			for (int k = 0; k < data.size;k++) {
				solutions[i].solution[k] = solutions[a].solution[k];
				solutions[i].row_1[k] = solutions[a].row_1[k];
				solutions[i].row_2[k] = solutions[a].row_2[k];
				solutions[i].col_1[k] = solutions[a].col_1[k];
				solutions[i].col_2[k] = solutions[a].col_2[k];
			}
		}
		a++;
	}

/*	for (int i = (*sizeSol) - rmsize ; i < (*sizeSol); i++) {
		free(solutions[i].solution);
		//solutions[i].solution = NULL;
		printf("%d test \n", solutions[i].solution[0]);
	}*/

	(*sizeSol) -= rmsize;


	if (toRem !=NULL)
		free(toRem);

	return solutions;
}



m_data * neighboorhood (m_data data, int** mat1, int** mat2, int * sizeSol, m_data* gSol, int sizeG) {

	int * tmp = NULL;

	m_data data_tmp;
	m_data * solutions = NULL;

// adds solutions
	for (int i = 0; i < data.size; i++) {
		tmp = calculate_costs(data, mat1, mat2, i);
		if (tmp[0] >= data.cost_1 || tmp[1] >= data.cost_2) {
			data_tmp = to_m_data(i, data, tmp, mat1, mat2);
			
			(*sizeSol)++;
			solutions = add_sol(solutions, data_tmp, (*sizeSol));
			//printf("second \n");
			//print_tab(solutions[(*sizeSol)-1].solution, data.size);
			//print_tab(solutions[(*sizeSol)-1].solution, data.size);

			//free_mdata(data_tmp);
		}
		free(tmp);
	}

	int rmsize = 0;
	int * toRem = NULL;

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
	if (toRem !=NULL)
		free(toRem);
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

	if (toRem !=NULL)
		free(toRem);

	return solutions;
}

void neighboorhood2 (m_data** solutions, m_data data, int** mat1, int** mat2, int * sizeSol, m_data* gSol, int sizeG) {

	int * tmp = NULL;

	m_data data_tmp;
	(*solutions) = malloc(sizeof(m_data) * (*sizeSol));

// adds solutions
	for (int i = 0; i < data.size; i++) {
		tmp = calculate_costs(data, mat1, mat2, i);
		if (tmp[0] >= data.cost_1 || tmp[1] >= data.cost_2) {

			//data_tmp = to_m_data(i, data, tmp, mat1, mat2);
			/* to m data en dur */
			int delta = 1;

			data_tmp.size = data.size;
			data_tmp.cost_1 = tmp[0];
			data_tmp.cost_2 = tmp[1];

			data_tmp.solution = (int*)malloc(sizeof(int) * data_tmp.size);
			for (int j = 0; j < data_tmp.size; j++)
				data_tmp.solution[j] = data.solution[j];

			if (data_tmp.solution[i] == 0 ) {
				data_tmp.solution[i] = 1;
				delta = 1;
			}
			else {
				data_tmp.solution[i] = 0;
				delta = -1;
			}

			data_tmp.row_1 = copy(data.row_1, data_tmp.size);
			update_row(data_tmp.size, &data_tmp.row_1, mat1, i, delta);

			data_tmp.row_2 = copy(data.row_2, data_tmp.size);
			update_row(data_tmp.size, &data_tmp.row_2, mat2, i, delta);
			
			data_tmp.col_1 = copy(data.col_1, data_tmp.size);
			update_col(data_tmp.size, &data_tmp.col_1, mat1, i, delta);

			data_tmp.col_2 = copy(data.col_2, data_tmp.size);
			update_col(data_tmp.size, &data_tmp.col_2, mat2, i, delta);




	/////
			
			(*sizeSol)++;
			(*solutions) = add_sol((*solutions), data_tmp, (*sizeSol));


			//printf("second \n");
			//print_tab(solutions[(*sizeSol)-1].solution, data.size);
			//print_tab(solutions[(*sizeSol)-1].solution, data.size);

			//free_mdata(data_tmp);
		}
		free(tmp);
	}

	int rmsize = 0;
	int * toRem = NULL;

	for (int i = 0; i < (*sizeSol); i++) {
		for (int j = i+1; j < (*sizeSol); j++) {
			if(((*solutions)[i].cost_1 > (*solutions)[j].cost_1 && (*solutions)[i].cost_2 >(*solutions)[j].cost_2) && (isInto(j, toRem, rmsize) == 0)){
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
//	print_tab(toRem, rmsize);

	(*solutions) = remove_sol((*solutions),(*sizeSol), toRem, rmsize);
	(*sizeSol) -= rmsize;

	rmsize = 0;
	if (toRem !=NULL)
		free(toRem);
	toRem = NULL;

	for (int i = 0; i < (*sizeSol); i++) {
		for (int j = 0; j < sizeG; j++) {
			if ((isInto(i, toRem, rmsize) == 0) ) {
				if (isTheSame((*solutions)[i].solution, gSol[j].solution, data.size) == 1) {
					rmsize++;
					toRem = add(toRem, i, rmsize);
				}
			}
		}
	}

	(*solutions)= remove_sol((*solutions),(*sizeSol), toRem, rmsize);
	(*sizeSol) -= rmsize;

	if (toRem !=NULL)
		free(toRem);
}



// removes from sol
void removeGlobal2(m_data * neigh, int sizeN, m_data** solutions, int * sizeSol) {
	int rmsize = 0;
	int * toRem = NULL;

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

	//(*solutions) = remove_sol((*solutions),(*sizeSol), toRem, rmsize);

	int a = 0;
	for (int i = 0; i < (*sizeSol) - rmsize; i++) {
		for (int j = 0; j < rmsize ;j++) {
			if (isInto(a, toRem, rmsize) == 1) {
			//	printf("%d remove \n ", a);
				a++;
			}
		}
		if (i != a) {
			(*solutions)[i].cost_1 = (*solutions)[a].cost_1;
			(*solutions)[i].cost_2 = (*solutions)[a].cost_2;
			for (int k = 0; k < neigh[0].size ;k++) {
				(*solutions)[i].solution[k] = (*solutions)[a].solution[k];
				(*solutions)[i].row_1[k] = (*solutions)[a].row_1[k];
				(*solutions)[i].row_2[k] = (*solutions)[a].row_2[k];
				(*solutions)[i].col_1[k] = (*solutions)[a].col_1[k];
				(*solutions)[i].col_2[k] = (*solutions)[a].col_2[k];
			}
		}
		a++;
	}

	for (a = a+1; a < (*sizeSol); a++){
		free((*solutions)[a].solution);
	} 


	(*sizeSol) -= rmsize;
	
	if(toRem != NULL) {
		free(toRem);
	}
}

/// free


void free_matrix(int **matrix, int size_x)
{
    for(int i = 0; i < size_x; i++)
        free(matrix[i]);
    free(matrix);
}
void free_mdata(m_data d) {
	if (d.solution !=NULL) {
		free(d.solution);
		d.solution = NULL;
	}

	if (d.row_1 !=NULL)
		free(d.row_1);

	if (d.row_2 !=NULL)
		free(d.row_2);

	if (d.col_1 !=NULL)
		free(d.col_1);

	if (d.col_2 !=NULL)
		free(d.col_2);
}

void free_tab(m_data * d, int d_size, int size) {

	/*for (int i = 0; i < d_size; i++) {
		free(d[i].solution);
	} */ 
	if (d!= NULL)
		free(d);

}