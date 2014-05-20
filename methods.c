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

int isIntoMark(int c1, int c2, int** cs, int size) {
	for (int i = 0; i < size; i++) {
		if (c1 == cs[i][0] && c2 == cs[i][1]) {
			return 1;
		}
	}
	return 0;
}

int isIntoSol(int c1, int c2, int* cs1, int* cs2, int sizeSol) {
	for (int i = 0; i < sizeSol; i++){
		if (c1 == cs1[i] && c2 == cs2[i]) {
			return 1;
		}
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
	srand(time(NULL));
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
		max = solu.dat.size * 50;

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
			break;
	}



	// remove first sols 
	int nbr = 0;
	while (nbr < 3) {
		for (int i = 0; i < sizeSol / 2; i++) {
				costs1[i] = costs1[(sizeSol / 2) + i];
				costs2[i] = costs2[(sizeSol / 2) + i];
				for (int k = 0; k < solu.dat.size;k++) {
					solutions[i][k] = solutions[(sizeSol / 2) + i][k];
					rows1[i][k] = rows1[(sizeSol / 2) + i][k];
					rows2[i][k] = rows2[(sizeSol / 2) + i][k];
					cols1[i][k] = cols1[(sizeSol / 2) + i][k];
					cols2[i][k] = cols2[(sizeSol / 2) + i][k];
				}
			
		}
		sizeSol /= 2;

		index /=2;
		while (sizeSol < max - (solu.dat.size + 100)) {
			index = globalNeigh2 (index, solu.dat.size, solu.mat1, solu.mat2, &sizeSol, &solutions, &rows1, &rows2, &cols1, &cols2, &costs1, &costs2);
			if (index == -1)
				index = sizeSol - (sizeSol /2);
		}
		nbr++;
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

int global2(char* fileName) {

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
		max = solu.dat.size * 120;

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



///////////////////////////////NEIGH////////////////////
//////////////////////////////////////////////////////


	int index = 0;
	while (sizeSol < max - (solu.dat.size + 100)) {
		index = globalNeigh2 (index, solu.dat.size, solu.mat1, solu.mat2, &sizeSol, &solutions, &rows1, &rows2, &cols1, &cols2, &costs1, &costs2);
		if (index == -1)
			index = sizeSol / 2;
	}


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


// when solutions number > 400 => removes 200 + just dominant neigh into loop for
int global3(char* fileName) {
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
	int sizeMark = 0;
	int max;

	if (solu.dat.size < 100)
		max = 50000;
	else
		max = solu.dat.size * 10;

	int ** solutions = (int**)malloc(sizeof(int*) * max);
	int ** rows1 = (int**)malloc(sizeof(int*) * max);
	int ** rows2 = (int**)malloc(sizeof(int*) * max);
	int ** cols1 = (int**)malloc(sizeof(int*) * max);
	int ** cols2 = (int**)malloc(sizeof(int*) * max);

	int** mark = (int**)malloc(sizeof(int*) * max);

	int* costs1 = (int*)malloc(sizeof(int) * max);
	int* costs2 = (int*)malloc(sizeof(int) * max);
	for (int i = 0; i < max; i++) {
		solutions[i] = malloc(sizeof(int) * solu.dat.size);
		rows1[i] = malloc(sizeof(int) * solu.dat.size);
		rows2[i] = malloc(sizeof(int) * solu.dat.size);
		cols1[i] = malloc(sizeof(int) * solu.dat.size);
		cols2[i] = malloc(sizeof(int) * solu.dat.size);
		mark[i] = malloc(sizeof(int) * 2);
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
	int ok = 0;


	int ind = 0;
	int finished = 0;
	int nbr2 = 0;

	int testcost1;
	int testcost2;
	while ( finished == 0/*(number <  500) && (sizeSol <= (max - 2000))*/ /* while sizeSol != sizeMark */) {
		
		ok = 0;
		if (sizeSol > 400) {
			sizeSol = 200;
			ok = 1;
			printf("number =  %d  and sizesol = %d\n", number, sizeSol);
		}

		oldSol = sizeSol;

		if (sizeSol > 0) {
			oldCost[0] = costs1[sizeSol - 1];
			oldCost[1] = costs2[sizeSol - 1];
		}

///////////////////////////////NEIGH////////////////////
//////////////////////////////////////////////////////
		/* marquage : 
			matrice : nbmax * 2 + size
			verif si elem dans matrice encore dans costs1 et costs 2
			si dans costs1 et costs 2 mais pas dans matrice : add
			si sizeSol = size mat => finir 
		*/

		// while ind is into mark => find another ind
		srand(time(NULL));
		ind = rand() % sizeSol;

			
		globalNeigh (ind, solu.dat.size, solu.mat1, solu.mat2, &sizeSol, &solutions, &rows1, &rows2, &cols1, &cols2, &costs1, &costs2);
		int test;
		int temp;
		if( (oldSol == sizeSol && (oldCost[0] == costs1[sizeSol -1] && oldCost[1] == costs2[sizeSol -1])) || ok == 1){
			testcost1 = costs1[sizeSol - 1];
			testcost2 = costs2[sizeSol - 1];
			temp = 0;
			for (int i = 0; i < sizeSol; i++){
				oldCost[0] = costs1[sizeSol - 1];
				oldCost[1] = costs2[sizeSol - 1];
				oldSol = sizeSol;
				number++;
				test = globalNeigh2 (i, solu.dat.size, solu.mat1, solu.mat2, &sizeSol, &solutions, &rows1, &rows2, &cols1, &cols2, &costs1, &costs2);
				temp = i;
				if(test > 0){
					printf(" == %d ==== %d AND %d \n %d in %d\n", oldCost[0], oldCost[1], number, i, sizeSol);

					break;					
				}
			}
			if (temp >= sizeSol - 1) {
				finished = 1;
			}
		}
		/*if (sizeSol > 100){
			sizeSol = 50;
		//	printf("CLEAN now : 50 sols\n");
		}*/

		number++;
	}

	free(oldCost);


	/*for (int i = 0; i < sizeSol; i++) {
		printf("index i = %d\ncosts : %d | %d \n",i, costs1[i], costs2[i] );
		printf("costs with init : %d | %d\n",init_cost(solu.mat1, solu.dat.size, solutions[i]), init_cost(solu.mat2, solu.dat.size, solutions[i]) );
	}*/


	write_res(costs1, costs2, sizeSol, fileName);



/////////////////////////FREE////////////////////////////
////////////////////////////////////////////////////////
	free_matrix(solutions, max);
	free_matrix(mark, max);
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

/// FULL LOCAL SEARCH 

int global4(char* fileName) {
/////////////// INIT////////////////////
////////////////////////////////////////
	first_s solu;

	// adds nbSol somewhere

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
	int sizeMark = 0;
	int max;

	if (solu.dat.size < 100)
		max = 50000;
	else
		max = solu.dat.size * 150;

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

	int* numberOfSol = (int*)malloc(sizeof(int) * max);
	int sizeNOS = 1;
	numberOfSol[0] = 1;


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
	int ok = 0;


	int ind = 0;
	int finished = 0;
	int nbr2 = 0;

	int testcost1;
	int testcost2;
	while ( finished == 0/*(number <  500) && (sizeSol <= (max - 2000))*/ /* while sizeSol != sizeMark */) {
		if ((number % 100) == 0) {
			numberOfSol[sizeNOS] = sizeSol;		
			printf("sizeSol = %d\n", sizeSol);
			sizeNOS++;
		}

		oldSol = sizeSol;

		if (sizeSol > 0) {
			oldCost[0] = costs1[sizeSol - 1];
			oldCost[1] = costs2[sizeSol - 1];
		}

///////////////////////////////NEIGH////////////////////
//////////////////////////////////////////////////////
		/* marquage : 
			matrice : nbmax * 2 + size
			verif si elem dans matrice encore dans costs1 et costs 2
			si dans costs1 et costs 2 mais pas dans matrice : add
			si sizeSol = size mat => finir 
		*/

		// while ind is into mark => find another ind
		srand(time(NULL));
		ind = rand() % sizeSol;

			
		globalNeigh (ind, solu.dat.size, solu.mat1, solu.mat2, &sizeSol, &solutions, &rows1, &rows2, &cols1, &cols2, &costs1, &costs2);

		int test;
		int temp;
		if( (oldSol == sizeSol && (oldCost[0] == costs1[sizeSol -1] && oldCost[1] == costs2[sizeSol -1]))){
			testcost1 = costs1[sizeSol - 1];
			testcost2 = costs2[sizeSol - 1];
			temp = 0;
			for (int i = 0; i < sizeSol; i++){
					if ((number % 100) == 0) {
						numberOfSol[sizeNOS] = sizeSol;
						sizeNOS++;
					}


				oldCost[0] = costs1[sizeSol - 1];
				oldCost[1] = costs2[sizeSol - 1];
				oldSol = sizeSol;
				
				test = globalNeigh3(i, solu.dat.size, solu.mat1, solu.mat2, &sizeSol, &solutions, &rows1, &rows2, &cols1, &cols2, &costs1, &costs2, i);
				temp = i;
				if (number % 10000 == 0){
					printf("WRITING\n");
					write_res(costs1, costs2, sizeSol, "tempRes");
					printf("DONE");
				}

				number++;
				if(test != 1000000){
					printf(" == %d ==== %d AND %d \n %d in %d - new i is %d\n", oldCost[0], oldCost[1], number, i, sizeSol, test);
					break;				
				}
			}
			if ((temp >= sizeSol - 1) || sizeSol > max - (solu.dat.size*2)) {
				finished = 1;
			}
		}


		if (number % 10000 == 0){
			printf("WRITING\n");
			write_res(costs1, costs2, sizeSol, "tempRes");
			printf("DONE");
		}

		number++;

		if(sizeSol > max - (solu.dat.size*2)) {
			finished = 1;
		}
	}

	free(oldCost);


	/*for (int i = 0; i < sizeSol; i++) {
		printf("index i = %d\ncosts : %d | %d \n",i, costs1[i], costs2[i] );
		printf("costs with init : %d | %d\n",init_cost(solu.mat1, solu.dat.size, solutions[i]), init_cost(solu.mat2, solu.dat.size, solutions[i]) );
	}*/


	write_res(costs1, costs2, sizeSol, fileName);

	write_nb(numberOfSol, sizeNOS,fileName);



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

int globalNeigh3 ( int currentSol, int size, int ** mat1, int ** mat2, int* sizeSol, int *** sol, int*** rows1, int*** rows2, int*** cols1, int*** cols2, int** costs1, int**costs2, int cIndex) {
	///////////// ADDS EVERY SOLUTION WITH AN EQUIVALENT OR BETTER COST ///////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	// TODO : if with maximal size ...

	int old = (*sizeSol);
	int * tmp = NULL;
	int toReturn = 1000000;


			//		printf("test \n");

	for (int i = 0; i < size; i++) {
		tmp = calculate_costs_global((*costs1)[currentSol], (*costs2)[currentSol], (*rows1)[currentSol], (*rows2)[currentSol], (*cols1)[currentSol],
		(*cols2)[currentSol], (*sol)[currentSol], mat1, mat2, i);

		if((tmp[0] >= (*costs1)[currentSol] || tmp[1] >= (*costs2)[currentSol]) && (tmp[0] != (*costs1)[currentSol] &&  tmp[1] != (*costs2)[currentSol]  )) {
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
	int * toRem = malloc(sizeof(int) * 100000);

	for (int i = 0; i < (*sizeSol); i++) {
		for (int j = i +1; j < (*sizeSol); j++) {
			if((*costs1)[i] > (*costs1)[j] && (*costs2)[i] > (*costs2)[j] && (isInto(j, toRem, rmsize) == 0)) {
				toRem[rmsize] = j;
				if (j <= cIndex && j < toReturn){
					toReturn = j;
				}
				rmsize++;
			}
			else if ((*costs1)[i] < (*costs1)[j] && (*costs2)[i] < (*costs2)[j]&& (isInto(i, toRem, rmsize) == 0)) {
				toRem[rmsize] = i;
				if (i <= cIndex && i < toReturn) {
					toReturn = i;
				}
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

	return toReturn;
	
}

int globalNeigh ( int currentSol, int size, int ** mat1, int ** mat2, int* sizeSol, int *** sol, int*** rows1, int*** rows2, int*** cols1, int*** cols2, int** costs1, int**costs2 /* see for gsol & sizeG */) {
	///////////// ADDS EVERY SOLUTION WITH AN EQUIVALENT OR BETTER COST ///////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	// TODO : if with maximal size ...

	int old = (*sizeSol);
	int * tmp = NULL;
	int toReturn = 0;


			//		printf("test \n");

	for (int i = 0; i < size; i++) {
		tmp = calculate_costs_global((*costs1)[currentSol], (*costs2)[currentSol], (*rows1)[currentSol], (*rows2)[currentSol], (*cols1)[currentSol],
		(*cols2)[currentSol], (*sol)[currentSol], mat1, mat2, i);

		if((tmp[0] >= (*costs1)[currentSol] || tmp[1] >= (*costs2)[currentSol]) && (tmp[0] != (*costs1)[currentSol] &&  tmp[1] != (*costs2)[currentSol]  )) {
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
	int * toRem = malloc(sizeof(int) * 100000);

	for (int i = 0; i < (*sizeSol); i++) {
		for (int j = i +1; j < (*sizeSol); j++) {
			if((*costs1)[i] > (*costs1)[j] && (*costs2)[i] > (*costs2)[j] && (isInto(j, toRem, rmsize) == 0)) {
				toRem[rmsize] = j;
				if (j < old){
					toReturn = 1;
				}
				rmsize++;
			}
			else if ((*costs1)[i] < (*costs1)[j] && (*costs2)[i] < (*costs2)[j]&& (isInto(i, toRem, rmsize) == 0)) {
				toRem[rmsize] = i;
				if (i < old) {
					toReturn = 1;
				}
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

	return toReturn;
	
}

int globalNeigh2 ( int currentSol, int size, int ** mat1, int ** mat2, int* sizeSol, int *** sol, int*** rows1, int*** rows2, int*** cols1, int*** cols2, int** costs1, int**costs2 /* see for gsol & sizeG */) {
///////////// ADDS EVERY SOLUTION WITH AN EQUIVALENT OR BETTER COST ///////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	// TODO : if with maximal size ...

	int old = (*sizeSol);
	int * tmp = NULL;
	int number = 0;


			//		printf("test \n");

	for (int i = 0; i < size; i++) {
		tmp = calculate_costs_global((*costs1)[currentSol], (*costs2)[currentSol], (*rows1)[currentSol], (*rows2)[currentSol], (*cols1)[currentSol],
		(*cols2)[currentSol], (*sol)[currentSol], mat1, mat2, i);

		if(tmp[0] >= (*costs1)[currentSol] && tmp[1] >= (*costs2)[currentSol] && (tmp[0] != (*costs1)[currentSol] &&  tmp[1] != (*costs2)[currentSol]  )) {
			int delta = 1;
			number++;

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

	return number;
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

void write_nb(int* solSize, int size, char* fileName) {
	FILE* file = NULL;
	char* line = malloc(sizeof(char)* (strlen(fileName) + 5)); 	
	strcpy(line, fileName);
	strcat(line,"NBSOL");
    file = fopen(line, "w");
 
    if (file != NULL)
    {
        for (int i = 0; i < size; i++) {

        	fprintf(file, "%d", solSize[i]);
        	fprintf(file, " ") ;
        	fprintf(file, "%d", i*100);
        	fprintf(file, "\n") ;

        }

        fclose(file);
    }
    free(line);
}

/// free

void free_matrix(int **matrix, int size_x)
{
    for(int i = 0; i < size_x; i++)
        free(matrix[i]);
    free(matrix);
}