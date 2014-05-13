#include "methods.h"
#include <string.h>


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

int sameCost(int c1, int c2, int cc1, int cc2) {
	if (c1 == cc1 && c2 == cc2)
		return 1;
	else
		return 0;
}

int * copy(int const * sol, int size) {
	int * tmp = (int*)malloc(sizeof(int) * size);
	memcpy(tmp, sol, size * sizeof(int));

	return tmp;
}

int exists(int c1, int c2, int* cs1, int* cs2, int size) {
	for (int i = 0; i < size ; i++ ) {
		if (c1 == cs1[i] || c2 == cs2[i] )
			return 1;
	}
	return 0;
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


int* calculate_costs_global(int cost_1, int cost_2, int* row_1, int* row_2, int* col_1, int* col_2, int* solution, int ** mat1, int ** mat2, int index) {
	int* temp = (int*)malloc(sizeof(int) * 2);
	// print_tab(d.row_2, 5);
	temp[0] = cost_1 + delta_index(mat1, row_1, col_1, solution, index);
	temp[1] = cost_2 + delta_index(mat2, row_2, col_2, solution, index);
	return temp;
}

int global(char* fileName) {

/////////////// INIT////////////////////
////////////////////////////////////////
	first_s solu;

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
	int max;

	if (solu.dat.size < 100)
		max = 50000;
	else
		max = solu.dat.size * 20;

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

	printf(" INIT COST %d %d \n", costs1[0], costs2[0]);


///// Global loop ////////////
//////////////////////////////


	int number = 0;
	int oldSol = 0;
	int * oldCost = malloc(sizeof(int) * 2);


/*
	while (number <  10) {
		printf("number =  %d \n", number);

		oldSol = sizeSol;
		if (sizeSol > 0) {
			oldCost[0] = costs1[sizeSol - 1];
			oldCost[1] = costs2[sizeSol - 1];
		}
///////////////////////////////NEIGH////////////////////
//////////////////////////////////////////////////////


		for (int i = 0; i < sizeSol; i++) {
			globalNeigh (i, solu.dat.size, solu.mat1, solu.mat2, &sizeSol, &solutions, &rows1, &rows2, &cols1, &cols2, &costs1, &costs2);

			if (sizeSol > 100)
				break;
		}

		if (oldSol - sizeSol == 0) {
			if (sameCost (oldCost[0], oldCost[1], costs1[sizeSol - 1], costs2[sizeSol - 1] ) == 1)
				break;
		}

		number++;
	}

	free(oldCost);
*/
	int index = 0;
	while (sizeSol < max - (solu.dat.size + 100)) {
		index = globalNeigh2 (index, solu.dat.size, solu.mat1, solu.mat2, &sizeSol, &solutions, &rows1, &rows2, &cols1, &cols2, &costs1, &costs2);
		if (index == -1)
			index = 0;
	}



	/* remove first sols */
	for (int i = 0; i < sizeSol / 2; i++) {
		
	}
	sizeSol /= 2;

	index = 0;
	while (sizeSol < max - (solu.dat.size + 100)) {
		index = globalNeigh2 (index, solu.dat.size, solu.mat1, solu.mat2, &sizeSol, &solutions, &rows1, &rows2, &cols1, &cols2, &costs1, &costs2);
		if (index == -1)
			index = 0;
		/* remove first sols */
	}

////////////////// VERIFICATION /////////////////////////
////////////////////////////////////////////////////////
/*	for (int i = 0; i < sizeSol; i++) {
		printf("index i = %d\ncosts : %d | %d \n",i, costs1[i], costs2[i] );
		//printf("costs with init : %d | %d\n",init_cost(solu.mat1, solu.dat.size, solutions[i]), init_cost(solu.mat2, solu.dat.size, solutions[i]) );
	}*/

	write_res(costs1, costs2, sizeSol, fileName);



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


			//		printf("test \n");

	for (int i = 0; i < size; i++) {
		tmp = calculate_costs_global((*costs1)[currentSol], (*costs2)[currentSol], (*rows1)[currentSol], (*rows2)[currentSol], (*cols1)[currentSol],
		(*cols2)[currentSol], (*sol)[currentSol], mat1, mat2, i);

		if(tmp[0] >= (*costs1)[currentSol] || tmp[1] >= (*costs2)[currentSol] && (tmp[0] != (*costs1)[currentSol] &&  tmp[1] != (*costs2)[currentSol]  )) {
			int delta = 1;

			// fill
			// delta
			if ((*sol)[currentSol][i] == 0 ) {
				(*sol)[(*sizeSol)][i] = 1;
				delta = 1;
			}
			else {
				(*sol)[(*sizeSol)][i] = 0;
				delta = -1;
			}


			for (int j = 0; j < size; j++) {
				if (j != i) {
					(*sol)[(*sizeSol)][j] = (*sol)[currentSol][j];
					(*rows1)[(*sizeSol)][j] = (*rows1)[currentSol][j] + mat1[j][i] * delta;
					(*rows2)[(*sizeSol)][j] = (*rows2)[currentSol][j] + mat2[j][i] * delta;
					(*cols1)[(*sizeSol)][j] = (*cols1)[currentSol][j] + mat1[i][j] * delta;
					(*cols2)[(*sizeSol)][j] = (*cols2)[currentSol][j] + mat2[i][j] * delta;
				}
				else {
					(*rows1)[(*sizeSol)][j] = (*rows1)[currentSol][j];
					(*rows2)[(*sizeSol)][j] = (*rows2)[currentSol][j];
					(*cols1)[(*sizeSol)][j] = (*cols1)[currentSol][j];
					(*cols2)[(*sizeSol)][j] = (*cols2)[currentSol][j];
				}
			}
			(*costs1)[(*sizeSol)] = tmp[0];
			(*costs2) [(*sizeSol)] = tmp[1];

	/*		if (init_cost(mat1, size, (*sol)[(*sizeSol)]) != tmp[0]) {
				print_tab((*sol)[(*sizeSol)], size);
				printf("index = %d \n", i);
				printf("problem \n");
				break;
			}*/

			(*sizeSol)++;
		}
		free(tmp);
	}


/////////////// REMOVES //////////
////////////////////////////////

//// TODO : try to remove into the first loop
//// idea : write with the j and the i how to set the a

	int rmsize = 0;
	int * toRem = malloc(sizeof(int) * 1000);

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

	
	int a = 0;
	for (int i = 0; i < (*sizeSol) - rmsize; i++) {
		for (int j = 0; j < rmsize ;j++) {
			if (isInto(a, toRem, rmsize) == 1) {
			//	printf("%d remove \n ", a);
				a++;
			}
			else {
				break;
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

int globalNeigh2 ( int currentSol, int size, int ** mat1, int ** mat2, int* sizeSol, int *** sol, int*** rows1, int*** rows2, int*** cols1, int*** cols2, int** costs1, int**costs2 /* see for gsol & sizeG */) {
	///////////// ADDS EVERY SOLUTION WITH AN EQUIVALENT OR BETTER COST ///////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	// TODO : if with maximal size ...

/////////////// REMOVES //////////
////////////////////////////////
/*	if ((*sizeSol) >= 2500) { 
		int rmsize = 0;
		int * toRem = malloc(sizeof(int) * 100000);
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

		return rmsize;
	}*/
	int toReturn = -1;
	int * old = malloc(sizeof(int) * 2);
	old[0] = -100000000;
	old[1] = -100000000;

	int * tmp = NULL;
	for (int i = 0; i < size; i++) {
		tmp = calculate_costs_global((*costs1)[currentSol], (*costs2)[currentSol], (*rows1)[currentSol], (*rows2)[currentSol], (*cols1)[currentSol],
		(*cols2)[currentSol], (*sol)[currentSol], mat1, mat2, i);

		if (exists(tmp[0], tmp[1], (*costs1), (*costs2), size) == 0){

			if(tmp[0] >= (*costs1)[currentSol] || tmp[1] >= (*costs2)[currentSol]) {
				

				if (tmp[0] > old[0] && tmp[1] > old[1]) {
					toReturn = (*sizeSol);
					old[0] = tmp[0] ;
					old[1] = tmp[1];
				}
				int delta = 1;

				// fill
				// delta
				if ((*sol)[currentSol][i] == 0 ) {
					(*sol)[(*sizeSol)][i] = 1;
					delta = 1;
				}
				else {
					(*sol)[(*sizeSol)][i] = 0;
					delta = -1;
				}


				for (int j = 0; j < size; j++) {
					if (j != i) {
						(*sol)[(*sizeSol)][j] = (*sol)[currentSol][j];
						(*rows1)[(*sizeSol)][j] = (*rows1)[currentSol][j] + mat1[j][i] * delta;
						(*rows2)[(*sizeSol)][j] = (*rows2)[currentSol][j] + mat2[j][i] * delta;
						(*cols1)[(*sizeSol)][j] = (*cols1)[currentSol][j] + mat1[i][j] * delta;
						(*cols2)[(*sizeSol)][j] = (*cols2)[currentSol][j] + mat2[i][j] * delta;
					}
					else {
						(*rows1)[(*sizeSol)][j] = (*rows1)[currentSol][j];
						(*rows2)[(*sizeSol)][j] = (*rows2)[currentSol][j];
						(*cols1)[(*sizeSol)][j] = (*cols1)[currentSol][j];
						(*cols2)[(*sizeSol)][j] = (*cols2)[currentSol][j];
					}
				}
				(*costs1)[(*sizeSol)] = tmp[0];
				(*costs2) [(*sizeSol)] = tmp[1];

				(*sizeSol)++;
			}
		}

		free(tmp);
	}

	free(old);
	return toReturn;
}

void write_res(int * costs1, int * costs2, int size, char* fileName) {
	FILE* file = NULL;
	char* line = malloc(sizeof(char)* (strlen(fileName) + 4)); 	
	strcpy(line, fileName);
	strcat(line,".res");
    file = fopen(line, "w");
 
    if (file != NULL)
    {
        for (int i = 0; i < size; i++) {

        	fprintf(file, "%d", costs1[i]);
        	fprintf(file, " ") ;
        	fprintf(file, "%d", costs2[i]);
        	fprintf(file, "\n") ;

        }

        fclose(file);
    }
    free(line);
}

/*
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
*/
/// free


void free_matrix(int **matrix, int size_x)
{
    for(int i = 0; i < size_x; i++)
        free(matrix[i]);
    free(matrix);
}