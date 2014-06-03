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

void row_value(int ** row, int ** mat, int size, int * sol) {
	//(*row) = (int*)malloc(size*sizeof(int));
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

void col_value(int ** row, int ** mat, int size, int * sol) {
	//(*row) = (int*)malloc(size*sizeof(int));
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

int dominatedByEvery(int* dom, int* costs1, int* costs2, int sizeSol) {
	for (int i = 0; i < sizeSol; i++){
		if (dom[0] > costs1[i] || dom[1] > costs2[i])
			return 0;
	}
	return 1;
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

int global_hypervolume(char* fileName){
/////////////// INIT////////////////////
////////////////////////////////////////
	first_s solu;

	// size + matrix
	if (parse(fileName, &solu.dat.size, &solu.mat1, &solu.mat2) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	int sizeSol = 0;
	int sizeMark = 0;
	int max = 11;

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

	solu.dat.solution = malloc(sizeof(int)*solu.dat.size);

/////// FIRST PARETO ///////////
////////////////////////////////
	for (int k = 0; k < max - 1; k++) {
		int indicator = 0;
		while (indicator != 1) {

		srand(time(NULL));
		for (int m = 0; m < solu.dat.size; m++) {
			
			solu.dat.solution[m] = rand() % 2;
		}

		//costs
			solu.dat.cost_1 = init_cost(solu.mat1, solu.dat.size, solu.dat.solution);
			solu.dat.cost_2 = init_cost(solu.mat2, solu.dat.size, solu.dat.solution);
			int ok = 1;
			for (int j = 0; j < max; j++){
				//if ((solu.dat.cost_1 >= costs1[j] && solu.dat.cost_2 >= costs2[j]) || (solu.dat.cost_1 <= costs1[j] && solu.dat.cost_2 <= costs2[j])) {
				if ((solu.dat.cost_1 == costs1[j] && solu.dat.cost_2 == costs2[j]) ) {
					ok = 0;
					break;
				}
				
			}
			if (ok == 1){
				indicator= 1;
			}
		}
		for (int i = 0; i < solu.dat.size; i++) {
			solutions[k][i] = solu.dat.solution[i];
		}
		costs1[k] = solu.dat.cost_1;
		costs2[k] = solu.dat.cost_2;

		sizeSol++;

	//	printf(" INIT COST %d is : %d %d \n",k, costs1[k], costs2[k]);

	//	printf("costs with init : %d | %d\n",init_cost(solu.mat1, solu.dat.size, solutions[k]), init_cost(solu.mat2, solu.dat.size, solutions[k]) );
	}

////////// SORT SOLUTIONS (first cost is used)//////
	////////////////////////////////////////////////////

	int* tmpSol = malloc(sizeof(int) * solu.dat.size);
	int tmpC1;
	int tmpC2;
	int index;

	for (int i = 0; i < sizeSol - 1; i++){
		tmpC1 = costs1[i];
		index = i;
		for (int j = i + 1; j < sizeSol; j++) {
			if (costs1[j] < tmpC1) {
				tmpC1 = costs1[j];
				index = j;
			}

		}
		if (index != i) {
			for (int k = 0; k < solu.dat.size; k++){
				tmpSol[k] = solutions[index][k];
			}
			tmpC2 = costs2[index];
			for (int k = 0; k < solu.dat.size; k++) {
				solutions[index][k] = solutions[i][k];
				solutions[i][k] = tmpSol[k];
			}
			costs1[index] = costs1[i];
			costs2[index] = costs2[i];
			costs1[i] = tmpC1;
			costs2[i] = tmpC2;
		}
	}

	free(tmpSol);

	for (int i = 0; i < sizeSol; i++) {
			row_value(&rows1[i], solu.mat1, solu.dat.size, solutions[i]);
			row_value(&rows2[i], solu.mat2, solu.dat.size, solutions[i]);
			col_value(&cols1[i], solu.mat1, solu.dat.size, solutions[i]);
			col_value(&cols2[i], solu.mat2, solu.dat.size, solutions[i]);
	}
///////////////////////INIT HYPERVOLUME///////////////////
///////////////////////////////////////////////////////

	// Zref
	int x = -800000 ;
	int y = -800000 ;
	int hVol = 0;

	int* associatedHvol = malloc(sizeof(int) * max);
	int fX = 0;
	int fY = 0;

	if (costs1[0] < x || costs2[sizeSol - 1] < y) {
		printf("(costs2) = %d\n", costs2[sizeSol - 1] );
		printf("FAILURE WITH ZREF VALUES \n ");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < sizeSol; i++ ){
	//	printf("i = %d\n", i);
		if (i == 0){
			fX = x;
			fY = costs2[1];

		}
		else if (i == sizeSol - 1) {
			fX = costs1[i-1];
			fY = y;
		}
		else {
			fX = costs1[i - 1];
			fY = costs2[i + 1];
		}
		associatedHvol[i] = (costs1[i] - fX) * (costs2[i] - fY);
		printf("i %d AHV %d 1 cost %d\n",i, associatedHvol[i], costs1[i]);
		// TODO HVOL with fX fY and current (just add)
		hVol += (costs1[i] - fX)*(costs2[i] - y);
	}

///////////////////////////PRINCIPAL LOOP////////////////
/////////////////////////////////////////////////////////


	int * dominated = malloc(sizeof(int) * sizeSol);
	int sizeD = 0;
	int* tmp;

	int nbr = 0;
	while (sizeMark != sizeSol) {
		nbr++;
	// every solutions
			/////dominated list//////////////////
			sizeD = 0;
			for (int j = 0; j < sizeSol - 1; j++){
				for (int k = j+1; k < sizeSol; k++){
					if (costs1[j] < costs1[k] && costs2[j] < costs2[k]){
						dominated[sizeD] = j;
						sizeD++;
						break;
					}
				}
			}

			for (int i = 0; i < sizeSol; i++) {
		
			//	printf("i = %d\n",i );
				int ok = 0;
				int ind = -1;
				int toRem = -1;
				int tempRemValue = -1;
				//// neigh generation//////////////////////////////
				for (int index = 0; index < solu.dat.size; index++) {
				//	printf("index = %d\n",index );
					tmp = calculate_costs_global(costs1[i], costs2[i], rows1[i], rows2[i], cols1[i],
						cols2[i], solutions[i], solu.mat1, solu.mat2, index);

					if (isIntoSol(tmp[0], tmp[1], costs1, costs2,sizeSol) == 1){
					//	printf("CONTINUE\n");
						continue;
					}

				//	printf("before big if \n");

					///// if no dominated sols///////
					if (sizeD == 0 ){
					//	printf("GO\n");
						int test = 0;
						for (int k = 0; k < sizeSol; k++) {
							if (tmp[0] <= costs1[k] && tmp[1] <= costs2[k]){
								test = 1;
								break;
							}
						}

						///// if new sol non dominated by his "generator"///////////////
						if (test == 0) {
						//	printf("GO NUMBER 2\n");
							ind = 0;
							/////// add it //////////////////
							for (int a = 0; a < sizeSol; a++) {
								if (tmp[0] > costs1[a]){
									ind = a ;
								}
								else {
									break;
								}
							}
							if (ind!=0){
								ind++;
							}
							int valueOfI = i;
							for (int a = max - 1 ; a > ind; a--) {
								costs1[a] = costs1[a - 1];
								costs2[a] = costs2[a - 1];
								for(int f = 0; f < solu.dat.size; f++){
									solutions[a][f] = solutions[a-1][f];
								}
								if (a-1 == i){
									valueOfI = a;
								}
							}
							sizeSol++;
							costs1[ind] = tmp[0];
							costs2[ind] = tmp[1];
							for(int f = 0; f < solu.dat.size; f++){
									solutions[ind][f] = solutions[valueOfI][f];
							}

							if (solutions[valueOfI][index] == 0) {
								solutions[ind][index] = 1;
							}
							else {
								solutions[ind][index] = 0;
							}

							//printf("new Sol is at index %d \n", ind);

						/*	if (costs1[ind] != init_cost(solu.mat1, solu.dat.size, solutions[ind]) || costs2[ind] != init_cost(solu.mat2, solu.dat.size, solutions[ind]) ) {
								printf("ERROR WITH COSTS 1\n");
								return EXIT_FAILURE;
							}*/

							/////// check if new is dominant  ///////////////
							int dominant = 0;
							sizeD = 0;
							for (int a = 0; a < sizeSol; a++){
								if (costs2[ind] > costs2[a] && costs1[ind] > costs2[a]) {
									dominated[sizeD] = a;
									sizeD++;
									dominant = 1;								
								}
							}



							if (dominant == 0) {
								// calculate hVol
								for (int a = 0; a < sizeSol; a++ ){

									if (a == 0){
										fX = x;
										fY = costs2[1];

									}
									else if (a == sizeSol - 1) {
										fX = costs1[a-1];
										fY = y;
									}
									else {
										fX = costs1[a - 1];
										fY = costs2[a + 1];
									}
									associatedHvol[a] = (costs1[a] - fX) * (costs2[a] - fY);
								}
								// picks the lowest
								tempRemValue = associatedHvol[0];
								toRem = 0;
								for (int a = 1; a < max; a++) {
									if (associatedHvol[a] < tempRemValue) {
										toRem = a;
										tempRemValue = associatedHvol[a];
									}
								}
								if (toRem != ind) {
									ok = 1;
								}
							}
							else {
								///// TEMPORAIRE ///////////////////////
								toRem = dominated[sizeD/2];
								for (int a = 0; a < sizeD; a++){
									if (costs1[toRem] > costs1[dominated[a]] && costs2[toRem] > costs2[dominated[a]]) {
										toRem = dominated[a];
									}
								}
								ok = 1;							
							}
						}
						else {
							toRem = -1;
						}
					}

					// TO CONTINUE

					// if there are dominated sols
					else {
					//	printf("TODO \n");
					//	printf("here 2 \n");

						ind = 0;

							/////// add it //////////////////
							for (int a = 0; a < sizeSol; a++) {
								if (tmp[0] > costs1[a]){
									ind = a ;
								}
								else {
									break;
								}
							}
							if (ind!=0){
								ind++;
							}
							int valueOfI = i;
							for (int a = max - 1 ; a > ind; a--) {
								costs1[a] = costs1[a - 1];
								costs2[a] = costs2[a - 1];
								for(int f = 0; f < solu.dat.size; f++){
									solutions[a][f] = solutions[a-1][f];
								}
								if (a-1 == i){
									valueOfI = a;
								}
							}
							sizeSol++;
							costs1[ind] = tmp[0];
							costs2[ind] = tmp[1];


							//printf("new Sol is at index %d \n", ind);

							for(int f = 0; f < solu.dat.size; f++){
									solutions[ind][f] = solutions[valueOfI][f];
							}

							if (solutions[valueOfI][index] == 0) {
								solutions[ind][index] = 1;
								//printf("IF \n");
							}
							else {
								solutions[ind][index] = 0;
								//printf("ELSE \n");
							}

						/*	if (costs1[ind] != init_cost(solu.mat1, solu.dat.size, solutions[ind]) || costs2[ind] != init_cost(solu.mat2, solu.dat.size, solutions[ind]) ) {
								printf("ERROR WITH COSTS 2\n");
								return EXIT_FAILURE;
							}*/


							// update dominated and check if new is dominated
							sizeD = 0;
							int isInto = 0;
							for (int j = 0; j < sizeSol - 1; j++){
								for (int k = j+1; k < sizeSol; k++){
									if (costs1[j] < costs1[k] && costs2[j] < costs2[k]){
										dominated[sizeD] = j;
										sizeD++;
										if (j == ind){
											isInto = 1;
										}
										break;
									}
								}
							}

							///// TODO: determine which one is to remove HERE (only among dominated)

							///// temp (remove later) 
								toRem = dominated[sizeD/2];
								for (int a = 0; a < sizeD; a++){
									if (costs1[toRem] > costs1[dominated[a]] && costs2[toRem] > costs2[dominated[a]]) {
										toRem = dominated[a];
									}
								}
						

						//check if new solution is dominated => if not remove one of the dominated
						// else remove one of the dominated or, the solution

							if (toRem != ind) {
								ok = 1;
							}
	
					}

					if(toRem != ind && toRem != -1 && ind !=-1) {
						ok = 1;
					}
					else {
						ok = 0;
					}


					//free tmp somewhere
					free(tmp);

					if (toRem != -1) {
					// remove toRem
						//printf("removed sol is at index %d \n", toRem);
						for (int j = toRem; j < sizeSol - 1; j++) {
							costs1[j] = costs1[j+1];
							costs2[j] = costs2[j+1];
							for (int k = 0; k < solu.dat.size; k++) {
								solutions[j][k] = solutions[j+1][k];
							}
						}

						sizeSol--;

						for (int j = 0; j < sizeSol; j++) {
							row_value(&rows1[j], solu.mat1, solu.dat.size, solutions[j]);
							row_value(&rows2[j], solu.mat2, solu.dat.size, solutions[j]);
							col_value(&cols1[j], solu.mat1, solu.dat.size, solutions[j]);
							col_value(&cols2[j], solu.mat2, solu.dat.size, solutions[j]);
						}

						// update hVol

						hVol = 0;
						if (costs1[0] < x || costs2[sizeSol - 1] < y) {

							printf("2 - costs2 = %d not superior to %d \n", costs2[sizeSol - 1], x );
							printf("2 - costs1 = %d  not superior to %d\n", costs1[0], y );
							printf("FAILURE WITH ZREF VALUES \n ");
							return EXIT_FAILURE;
						}

						x = -800000;
						y = -800000;

						for (int ir = 0; ir < sizeSol; ir++ ){
							if (ir == 0){
								fX = x;
								fY = costs2[1];

							}
							else if (ir == sizeSol - 1) {
								fX = costs1[ir-1];
								fY = y;
							}
							else {
								fX = costs1[ir - 1];
								fY = costs2[ir + 1];
							}
							associatedHvol[ir] = (costs1[ir] - fX) * (costs2[ir] - fY);
							hVol += (costs1[ir] - fX)*(costs2[ir] - y);
						}
					}

			/*					for (int gr = 0; gr < sizeSol; gr++) {
					printf("index gr = %d\ncosts : %d | %d \n",gr, costs1[gr], costs2[gr] );	
					printf("costs with init : %d | %d\n",init_cost(solu.mat1, solu.dat.size, solutions[gr]), init_cost(solu.mat2, solu.dat.size, solutions[gr]) );
				}*/


					printf("i = %d index = %d\n", i, index);
					if (ok == 1){
					//	printf("########################################################## \n");
							break;
					}
				}


				//somewhere => if removed and into mark => remove from mark
				for (int j = 0; j < sizeMark; j++) {
					int isGood = 0;
					for (int k = 0; k < sizeSol; k++) {
						if (costs1[k] == mark[j][0]){
							isGood = 1;
							break;
						}
					}
					if (!isGood) {
						for (int a = j; a < sizeMark - 1; a++) {
							mark[a][0] = mark[a+1][0];
							mark[a][1] = mark[a+1][1];
						}
						sizeMark--;
					}
				}


				//mark i
				if (ok == 0) {
					printf("ADDED INTO MARK");
					mark[sizeMark][0] = costs1[i];
					mark[sizeMark][1] = costs2[i];
					sizeMark++;
				}
				printf("SIZE MARK = %d\n", sizeMark );
			}

		for (int i = 0; i < sizeSol; i++) {
			printf("/////////////////////////////////////////// \n");
			printf("index i = %d\ncosts : %d | %d \n",i, costs1[i], costs2[i] );
			//printf("HVOL : %d \n", associatedHvol[i]);
			//printf("costs with init : %d | %d\n",init_cost(solu.mat1, solu.dat.size, solutions[i]), init_cost(solu.mat2, solu.dat.size, solutions[i]) );
		}


		//break;//torem
	}

	free(dominated);

	for (int i = 0; i < sizeSol; i++) {
		printf("####################################### \n");
		printf("index i = %d\ncosts : %d | %d \n",i, costs1[i], costs2[i] );
		printf("costs with init : %d | %d\n",init_cost(solu.mat1, solu.dat.size, solutions[i]), init_cost(solu.mat2, solu.dat.size, solutions[i]) );
		printf("HVOL : %d \n", associatedHvol[i]);
	}


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

	free(solu.dat.solution);




	return EXIT_SUCCESS;
}

int global_hypervolume2(char* fileName){
/////////////// INIT////////////////////
////////////////////////////////////////
	first_s solu;

	// size + matrix
	if (parse(fileName, &solu.dat.size, &solu.mat1, &solu.mat2) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	int sizeSol = 0;
	int sizeMark = 0;
	int max = 11;

	int ** solutions = (int**)malloc(sizeof(int*) * max);
	int ** rows1 = (int**)malloc(sizeof(int*) * max);
	int ** rows2 = (int**)malloc(sizeof(int*) * max);
	int ** cols1 = (int**)malloc(sizeof(int*) * max);
	int ** cols2 = (int**)malloc(sizeof(int*) * max);
	int** mark = (int**)malloc(sizeof(int*) * max);
	int* costs1 = (int*)malloc(sizeof(int) * max);
	int* costs2 = (int*)malloc(sizeof(int) * max);
	int** already = (int**)malloc(sizeof(int*) * 5000);
	int sizeA = 0;

	int ** sizes = (int**)malloc(sizeof(int*) * max);
	int ** alreadyInto = (int**)malloc(sizeof(int*) * max);


	for (int i = 0; i < max; i++) {
		solutions[i] = malloc(sizeof(int) * solu.dat.size);
		rows1[i] = malloc(sizeof(int) * solu.dat.size);
		rows2[i] = malloc(sizeof(int) * solu.dat.size);
		cols1[i] = malloc(sizeof(int) * solu.dat.size);
		cols2[i] = malloc(sizeof(int) * solu.dat.size);
		alreadyInto[i] = malloc(sizeof(int) * solu.dat.size);
		mark[i] = malloc(sizeof(int) * 2);
		sizes[i] = malloc(sizeof(int) * 3);
		sizes[i][2] = 0;
	}
	for (int i = 0; i < 5000; i++) {		
		already[i] = malloc(sizeof(int) * 2);
	}
	
	solu.dat.solution = malloc(sizeof(int)*solu.dat.size);

/////// FIRST SOLS///////////
////////////////////////////////
	for (int k = 0; k < max - 1; k++) {
		int indicator = 0;
		while (indicator != 1) {

		//srand(time(NULL));
		for (int m = 0; m < solu.dat.size; m++) {
			
			solu.dat.solution[m] = rand() % 2;
		}

		//costs
			solu.dat.cost_1 = init_cost(solu.mat1, solu.dat.size, solu.dat.solution);
			solu.dat.cost_2 = init_cost(solu.mat2, solu.dat.size, solu.dat.solution);
			int ok = 1;
			for (int j = 0; j < max; j++){
				//if ((solu.dat.cost_1 >= costs1[j] && solu.dat.cost_2 >= costs2[j]) || (solu.dat.cost_1 <= costs1[j] && solu.dat.cost_2 <= costs2[j])) {
				if ((solu.dat.cost_1 == costs1[j] && solu.dat.cost_2 == costs2[j]) ) {
					ok = 0;
					break;
				}
				
			}
			if (ok == 1){
				indicator= 1;
			}
		}
		for (int i = 0; i < solu.dat.size; i++) {
			solutions[k][i] = solu.dat.solution[i];
		}
		costs1[k] = solu.dat.cost_1;
		costs2[k] = solu.dat.cost_2;
		sizes[k][0] = solu.dat.cost_1;
		sizes[k][1] = solu.dat.cost_2;
		sizeSol++;

	//	printf(" INIT COST %d is : %d %d \n",k, costs1[k], costs2[k]);

	//	printf("costs with init : %d | %d\n",init_cost(solu.mat1, solu.dat.size, solutions[k]), init_cost(solu.mat2, solu.dat.size, solutions[k]) );
	}

////////// SORT SOLUTIONS (first cost is used)//////
	////////////////////////////////////////////////////

	int* tmpSol = malloc(sizeof(int) * solu.dat.size);
	int tmpC1;
	int tmpC2;
	int index;

	for (int i = 0; i < sizeSol - 1; i++){
		tmpC1 = costs1[i];
		index = i;
		for (int j = i + 1; j < sizeSol; j++) {
			if (costs1[j] < tmpC1) {
				tmpC1 = costs1[j];
				index = j;
			}

		}
		if (index != i) {
			for (int k = 0; k < solu.dat.size; k++){
				tmpSol[k] = solutions[index][k];
			}
			tmpC2 = costs2[index];
			for (int k = 0; k < solu.dat.size; k++) {
				solutions[index][k] = solutions[i][k];
				solutions[i][k] = tmpSol[k];
			}
			costs1[index] = costs1[i];
			costs2[index] = costs2[i];
			costs1[i] = tmpC1;
			costs2[i] = tmpC2;
		}
	}

	free(tmpSol);

	for (int i = 0; i < sizeSol; i++) {
			row_value(&rows1[i], solu.mat1, solu.dat.size, solutions[i]);
			row_value(&rows2[i], solu.mat2, solu.dat.size, solutions[i]);
			col_value(&cols1[i], solu.mat1, solu.dat.size, solutions[i]);
			col_value(&cols2[i], solu.mat2, solu.dat.size, solutions[i]);
	}
///////////////////////INIT HYPERVOLUME///////////////////
///////////////////////////////////////////////////////

	// Zref
	int x = -800000 ;
	int y = -800000 ;
	int hVol = 0;

	int* associatedHvol = malloc(sizeof(int) * max);
	int fX = 0;
	int fY = 0;

	if (costs1[0] < x || costs2[sizeSol - 1] < y) {
		printf("(costs2) = %d\n", costs2[sizeSol - 1] );
		printf("FAILURE WITH ZREF VALUES \n ");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < sizeSol; i++ ){
	//	printf("i = %d\n", i);
		if (i == 0){
			fX = x;
			fY = costs2[1];

		}
		else if (i == sizeSol - 1) {
			fX = costs1[i-1];
			fY = y;
		}
		else {
			fX = costs1[i - 1];
			fY = costs2[i + 1];
		}
		associatedHvol[i] = (costs1[i] - fX) * (costs2[i] - fY);
		printf("i %d AHV %d 1 cost %d\n",i, associatedHvol[i], costs1[i]);
		// TODO HVOL with fX fY and current (just add)
		hVol += (costs1[i] - fX)*(costs2[i] - y);
	}

///////////////////////////PRINCIPAL LOOP////////////////
/////////////////////////////////////////////////////////


	int * dominated = malloc(sizeof(int) * sizeSol);
	int sizeD = 0;
	int* tmp;

	int nbr = 0;
	while (sizeMark != sizeSol) {
		nbr++;
	// every solutions
			/////dominated list//////////////////
			sizeD = 0;
			for (int j = 0; j < sizeSol - 1; j++){
				for (int k = j+1; k < sizeSol; k++){
					if (costs1[j] < costs1[k] && costs2[j] < costs2[k]){
						dominated[sizeD] = j;
						sizeD++;
						break;
					}
				}
			}

			for (int i = 0; i < sizeSol; i++) {
		
			//	printf("i = %d\n",i );
				int ok = 0;
				int ind = -1;
				int toRem = -1;
				int tempRemValue = -1;
				int good = 0;


				int cont = 0;
				for (int j = 0; j < sizeMark; j++){
					if (mark[j][0] == costs1[i] && mark[j][1] == costs2[i]){
						cont = 1;
						break;
					}

				}
				if (cont == 1){
					continue;
				}

				//// neigh generation//////////////////////////////

				//for (int index = 0; index < solu.dat.size; index++) {
				while(good != 1) {		

					// tmpIndex is the i index into sizes 
					int tmpIndex = -1;
					for (int g = 0; g < sizeSol; g++) {
						if (costs1[i] == sizes[g][0] && costs2[i] == sizes[g][1]){
							tmpIndex = g;
							break;
						}
					}

					// if i index is not found => error
					if (tmpIndex == -1) {

						for (int i = 0; i < sizeSol; i++) {
							printf("/////////////////////////////////////////// \n");
							printf("index i = %d\ncosts : %d | %d \n",i, costs1[i], costs2[i] );
						}

						printf("#################################################### \n");
						for (int i = 0; i < sizeSol; i++) {
							printf(" c1: %d c2:%d explored %d times \n", sizes[i][0], sizes[i][1], sizes[i][2]);
						}
						printf("\n WANTED %d, %d \n", costs1[i], costs2[i]);
						printf("ERROR \n");

						return EXIT_FAILURE;
					}


					// check if i is done
					if (sizes[tmpIndex][2] >= solu.dat.size - 1 ){
						ok = 0;
						printf("test before break \n");
						break;
					}


					//gets a random index and calculates associated cost

					//srand(time(NULL));			
					index = rand() % solu.dat.size;

					tmp = calculate_costs_global(costs1[i], costs2[i], rows1[i], rows2[i], cols1[i],
						cols2[i], solutions[i], solu.mat1, solu.mat2, index);

					if (isInto(index, alreadyInto[tmpIndex], sizes[tmpIndex][2]) == 1){
						printf("CONTINUE\n");
						continue;
					}

					int testAlready = 0;

					// if is already into marked sols (sols that's been generated)
					for (int ta = 0; ta < sizeA; ta++) {
						if (already[ta][0] == tmp[0] && already[ta][1] == tmp[1]){
							testAlready = 1;
							printf(" already explored \n");
							break;
						}
					}
					
					//###################################################################
				
						alreadyInto[tmpIndex][sizes[tmpIndex][2]] = index;
						sizes[tmpIndex][2] = sizes[tmpIndex][2] + 1;
						printf("added %d into %d \n",index, i);
					
					//###################################################################

						if (testAlready == 1){
							continue;
						}


					if (isIntoSol(tmp[0], tmp[1], costs1, costs2, sizeSol) == 1){
						continue;
					}
					///// if no dominated sols///////
					if (sizeD == 0 ){
					//	printf("GO\n");
						int test = 0;
						for (int k = 0; k < sizeSol; k++) {
							if (tmp[0] <= costs1[k] && tmp[1] <= costs2[k]){
								test = 1;
								break;
							}
						}

						///// if new sol non dominated by his "generator"///
						if (test == 0) {
						//	printf("GO NUMBER 2\n");
							ind = 0;
							/////// add it //////////////////
							for (int a = 0; a < sizeSol; a++) {
								if (tmp[0] > costs1[a]){
									ind = a ;
								}
								else {
									break;
								}
							}
							if (ind!=0){
								ind++;
							}
							int valueOfI = i;
							for (int a = max - 1 ; a > ind; a--) {
								costs1[a] = costs1[a - 1];
								costs2[a] = costs2[a - 1];
								for(int f = 0; f < solu.dat.size; f++){
									solutions[a][f] = solutions[a-1][f];
								}
								if (a-1 == i){
									valueOfI = a;
								}
							}
							sizeSol++;
							costs1[ind] = tmp[0];
							costs2[ind] = tmp[1];
							for(int f = 0; f < solu.dat.size; f++){
									solutions[ind][f] = solutions[valueOfI][f];
							}

							if (solutions[valueOfI][index] == 0) {
								solutions[ind][index] = 1;
							}
							else {
								solutions[ind][index] = 0;
							}



							/////// check if new is dominant  ///////////////
							int dominant = 0;
							sizeD = 0;
							for (int a = 0; a < sizeSol; a++){
								if (costs2[ind] > costs2[a] && costs1[ind] > costs2[a]) {
									dominated[sizeD] = a;
									sizeD++;
									dominant = 1;								
								}
							}



							if (dominant == 0) {
								// calculate hVol
								for (int a = 0; a < sizeSol; a++ ){

									if (a == 0){
										fX = x;
										fY = costs2[1];

									}
									else if (a == sizeSol - 1) {
										fX = costs1[a-1];
										fY = y;
									}
									else {
										fX = costs1[a - 1];
										fY = costs2[a + 1];
									}
									associatedHvol[a] = (costs1[a] - fX) * (costs2[a] - fY);
								}
								// picks the lowest
								tempRemValue = associatedHvol[0];
								toRem = 0;
								for (int a = 1; a < max; a++) {
									if (associatedHvol[a] < tempRemValue) {
										toRem = a;
										tempRemValue = associatedHvol[a];
									}
								}
								if (toRem != ind) {
									ok = 1;
								}
							}
							else {
								///// TEMPORAIRE ///////////////////////
								toRem = dominated[sizeD/2];
								for (int a = 0; a < sizeD; a++){
									if (costs1[toRem] > costs1[dominated[a]] && costs2[toRem] > costs2[dominated[a]]) {
										toRem = dominated[a];
									}
								}
								ok = 1;							
							}
						}
						else {
							toRem = -1;
						}
					}

					else {

						ind = 0;
							/////// add it //////////////////
							for (int a = 0; a < sizeSol; a++) {
								if (tmp[0] > costs1[a]){
									ind = a ;
								}
								else {
									break;
								}
							}
							if (ind!=0){
								ind++;
							}
							int valueOfI = i;
							for (int a = max - 1 ; a > ind; a--) {
								costs1[a] = costs1[a - 1];
								costs2[a] = costs2[a - 1];
								for(int f = 0; f < solu.dat.size; f++){
									solutions[a][f] = solutions[a-1][f];
								}
								if (a-1 == i){
									valueOfI = a;
								}
							}
							sizeSol++;
							costs1[ind] = tmp[0];
							costs2[ind] = tmp[1];


							//printf("new Sol is at index %d \n", ind);

							for(int f = 0; f < solu.dat.size; f++){
									solutions[ind][f] = solutions[valueOfI][f];
							}

							if (solutions[valueOfI][index] == 0) {
								solutions[ind][index] = 1;
								//printf("IF \n");
							}
							else {
								solutions[ind][index] = 0;
								//printf("ELSE \n");
							}

							// update dominated and check if new is dominated
							sizeD = 0;
							int isInto = 0;
							for (int j = 0; j < sizeSol - 1; j++){
								for (int k = j+1; k < sizeSol; k++){
									if (costs1[j] < costs1[k] && costs2[j] < costs2[k]){
										dominated[sizeD] = j;
										sizeD++;
										if (j == ind){
											isInto = 1;
										}
										break;
									}
								}
							}

							///// TODO: determine which one is to remove HERE (only among dominated)

							///// temp (remove later) 
								toRem = dominated[sizeD/2];
								for (int a = 0; a < sizeD; a++){
									if (costs1[toRem] > costs1[dominated[a]] && costs2[toRem] > costs2[dominated[a]]) {
										toRem = dominated[a];
									}
								}
						

						//check if new solution is dominated => if not remove one of the dominated
						// else remove one of the dominated or, the solution

							if (toRem != ind) {
								ok = 1;
							}
	
					}

					if(toRem != ind && toRem != -1 && ind !=-1) {
						ok = 1;
					}
					else {
						ok = 0;
					}


					//free tmp somewhere
					free(tmp);

					if (toRem != -1) {
						//printf("go \n");
						if (toRem != ind) {


							int tmpInd = -1;
							//printf("yay \n");
							for (int tr = 0; tr < max-1; tr++){
								if (costs1[toRem] == sizes[tr][0]  && costs2[toRem] == sizes[tr][1]) {
									tmpInd = tr;
									break;
								}
							}
						//printf(" toRem = %d index = %d \n", toRem, tmpInd);

							for (int ini = 0; ini < solu.dat.size; ini++){
								alreadyInto[tmpInd][ini] = -1;
							}


							sizes[tmpInd][0] = costs1[ind];
							sizes[tmpInd][1] = costs2[ind];
							sizes[tmpInd][2] = 0;
						}


					// remove toRem
						//printf("removed sol is at index %d \n", toRem);
						for (int j = toRem; j < sizeSol - 1; j++) {
							costs1[j] = costs1[j+1];
							costs2[j] = costs2[j+1];
							for (int k = 0; k < solu.dat.size; k++) {
								solutions[j][k] = solutions[j+1][k];
							}
						}


						sizeSol--;
//#########################################################
//#########################################################
//#########################################################


						for (int j = 0; j < sizeSol; j++) {
							row_value(&rows1[j], solu.mat1, solu.dat.size, solutions[j]);
							row_value(&rows2[j], solu.mat2, solu.dat.size, solutions[j]);
							col_value(&cols1[j], solu.mat1, solu.dat.size, solutions[j]);
							col_value(&cols2[j], solu.mat2, solu.dat.size, solutions[j]);
						}

						// update hVol

						hVol = 0;
						if (costs1[0] < x || costs2[sizeSol - 1] < y) {

							printf("2 - costs2 = %d not superior to %d \n", costs2[sizeSol - 1], x );
							printf("2 - costs1 = %d  not superior to %d\n", costs1[0], y );
							printf("FAILURE WITH ZREF VALUES \n ");
							return EXIT_FAILURE;
						}

						x = -800000;
						y = -800000;

						for (int ir = 0; ir < sizeSol; ir++ ){
							if (ir == 0){
								fX = x;
								fY = costs2[1];

							}
							else if (ir == sizeSol - 1) {
								fX = costs1[ir-1];
								fY = y;
							}
							else {
								fX = costs1[ir - 1];
								fY = costs2[ir + 1];
							}
							associatedHvol[ir] = (costs1[ir] - fX) * (costs2[ir] - fY);
							hVol += (costs1[ir] - fX)*(costs2[ir] - y);
						}
					}

					printf("i = %d index = %d\n", i, index);
					if (ok == 1){
					//	printf("########################################################## \n");
							good = 1;
					}

				}//endfor or endwhile (depends)

				for (int j = 0; j < sizeA; j++) {
					if (dominatedByEvery(already[j], costs1, costs2, sizeSol) == 1){
						for (int h = j; h < sizeA; h++) {
							already[h][0] = already[h+1][0];
							already[h][1] = already[h+1][1];
						}
						sizeA--;
					}
				}

				int toAddOk = 1;
				for (int j = 0; j < sizeSol; j++) {
					toAddOk = 1;
					for (int h = 0; h < sizeA; h++) {		
						if (costs1[j] == already[h][0] && costs2[j] == already[h][1]){
							toAddOk = 0;
						}
					}
					if (toAddOk == 1) {
						already[sizeA][0] = costs1[j];
						already[sizeA][1] = costs2[j];
						sizeA++;
					}
				}

				printf("sizeA = %d \n", sizeA);


				//somewhere => if removed and into mark => remove from mark
				for (int j = 0; j < sizeMark; j++) {
					int isGood = 0;
					for (int k = 0; k < sizeSol; k++) {
						if (costs1[k] == mark[j][0]){
							isGood = 1;
							break;
						}
					}
					if (!isGood) {
						for (int a = j; a < sizeMark - 1; a++) {
							mark[a][0] = mark[a+1][0];
							mark[a][1] = mark[a+1][1];
						}
						sizeMark--;
					}
				}

				//mark i
			/*	if (ok == 0) {
					printf("ADDED INTO MARK");
					mark[sizeMark][0] = costs1[i];
					mark[sizeMark][1] = costs2[i];
					sizeMark++;
				}
				*/
				//############################################################"
				// comment before and do : if a value on alreadyInto has been viewed solu.dat.size times and not already into : add it

				for (int j = 0; j < sizeSol; j++) {
					if (sizes[i][2] >= solu.dat.size - 1 && isIntoMark(sizes[i][0], sizes[i][1], mark, sizeMark) == 0){
						printf("ADDED INTO MARK");
						mark[sizeMark][0] = sizes[j][0];
						mark[sizeMark][1] = sizes[j][1];
						sizeMark++;
					}
				}

				printf("SIZE MARK = %d\n", sizeMark );
				if (sizeMark == max - 1){
					break;
				}

			}

		if (sizeMark == max - 1){
			break;
		}

		for (int i = 0; i < sizeSol; i++) {
			printf("/////////////////////////////////////////// \n");
			printf("index i = %d\ncosts : %d | %d \n",i, costs1[i], costs2[i] );
			//printf("HVOL : %d \n", associatedHvol[i]);
			//printf("costs with init : %d | %d\n",init_cost(solu.mat1, solu.dat.size, solutions[i]), init_cost(solu.mat2, solu.dat.size, solutions[i]) );
		}
		for (int i = 0; i < sizeSol; i++) {
			printf(" c1: %d c2:%d explored %d times \n", sizes[i][0], sizes[i][1], sizes[i][2]);
		}
		//break;//torem
	}

	free(dominated);

	for (int i = 0; i < sizeSol; i++) {
		printf("####################################### \n");
		printf("index i = %d\ncosts : %d | %d \n",i, costs1[i], costs2[i] );
		printf("costs with init : %d | %d\n",init_cost(solu.mat1, solu.dat.size, solutions[i]), init_cost(solu.mat2, solu.dat.size, solutions[i]) );
		printf("HVOL : %d \n", associatedHvol[i]);
	}
	//// SAVE


/////////////////////////FREE////////////////////////////
////////////////////////////////////////////////////////
	free_matrix(solutions, max);
	
	//free_matrix(mark, max);
	
	free_matrix(already,5000);
	
	free_matrix(rows1,  max);
	free_matrix(rows2,  max);
	free_matrix(cols1,  max);
	free_matrix(cols2,  max);
	
	free(costs1);
	free(costs2);
	
	free_matrix(sizes, max);
	
	//free_matrix(alreadyInto, max);
	
	free_matrix(solu.mat1, solu.dat.size);
	free_matrix(solu.mat2, solu.dat.size);

	free(solu.dat.solution);
	return EXIT_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////////////////
// when solutions number > 400 => removes 200 + just dominant neigh into loop for////////////
///////////////////////////////////////////////////////////////////////////////////////////
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

			
		globalNeigh(ind, solu.dat.size, solu.mat1, solu.mat2, &sizeSol, &solutions, &rows1, &rows2, &cols1, &cols2, &costs1, &costs2);

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
					printf(" == %d ==== %d AND %d \n %d in %d  - new i = %d\n", oldCost[0], oldCost[1], number, i, sizeSol, test);
					i = test;			
				}
				if (sizeSol > max - (solu.dat.size*2)) {
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