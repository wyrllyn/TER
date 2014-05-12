#include "methods.h"
#include "time.h"

int main(int argc, char** argv) {

	int max = 50000;
	// files
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	char * testFileName = "res/test.dat";

	clock_t begin, end;
	double time_spent;
	begin = clock();

	global(fileName);

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("EXEC TIME : %f \n", time_spent );

	return 0;
/*
	int sizeMat = 0;	
	int sizeSol = 0;
	m_data * solutions = malloc(sizeof(m_data) * max);


	//parse
	first_s solu = init(testFileName);


	// temp
	m_data * neigh = NULL;
	int sizeN = 0;


	sizeSol++;
	solutions[0] = solu.dat;

	printf("INITIAL COSTS : \n");
	print_cost(solutions[0]);

		printf("size %d \n ", solu.dat.size);


/*
	//////////////////////////////////////// Global method /////////////////
	for (int i = 0; i < sizeSol; i++) {
		printf("%d - %d \n", i, sizeSol);
		sizeN = 0;
		
		//neighboorhood4 (&neigh,solutions[i], solu.mat1, solu.mat2, &sizeN, solutions, sizeSol);
		neigh = neighboorhood3 (solutions[i], solu.mat1, solu.mat2, &sizeN, solutions, sizeSol);

		printf("sizeN = %d| sizeSol = %d \n", sizeN, sizeSol);
		
		solutions =  add_neigh(solutions, sizeSol, neigh, sizeN);

	/*	if (sizeSol + sizeN <= max) {
			for (int i = 0; i < sizeN; i++) {
				solutions[i + sizeSol] = neigh[i];
			}
		} */

		/*	if (sizeSol + sizeN <= max) {
				for (int j = 0; j < sizeN; j++) {
					solutions[j + sizeSol].solution = malloc(sizeof(int) * solu.dat.size);
					solutions[j + sizeSol].row_1 = malloc(sizeof(int) * solu.dat.size);
					solutions[j + sizeSol].row_2 = malloc(sizeof(int) * solu.dat.size);
					solutions[j + sizeSol].col_1 = malloc(sizeof(int) * solu.dat.size);
					solutions[j + sizeSol].col_2 = malloc(sizeof(int) * solu.dat.size);
					solutions[j + sizeSol].cost_1 = neigh[j].cost_1;
					solutions[j + sizeSol].cost_2 = neigh[j].cost_2;
					solutions[j + sizeSol].size = neigh[j].size;


					for (int k = 0; k < solu.dat.size; k++ ){
						solutions[j + sizeSol].solution[k] = neigh[j].solution[k];
						solutions[j + sizeSol].row_1[k] = neigh[j].row_1[k];
						solutions[j + sizeSol].row_2[k] = neigh[j].row_2[k];
						solutions[j + sizeSol].col_1[k] = neigh[j].col_1[k];
						solutions[j + sizeSol].col_2[k] = neigh[j].col_2[k];
					}

					free(neigh[j].solution);
					neigh[j].solution = NULL;
					free(neigh[j].row_1);
					neigh[j].row_1 = NULL;
					free(neigh[j].row_2);
					free(neigh[j].col_1);
					free(neigh[j].col_2);
				}
			}*/

		/*	for (int k = 0; k < sizeN; k++){
				print_tab(neigh[k].solution, 5);
			}
			for (int k = 0; k < sizeSol; k++) {
				print_tab(solutions[k].solution, 5);
			}*//*

		if (neigh != NULL){
			free(neigh);
			neigh = NULL;
		}
		sizeSol += sizeN;		

	}

	printf("done \n");
	for (int i = 0; i < sizeSol; i++) {
		printf("index i = %d on %d \n", i, sizeSol);
		print_cost(solutions[i]);
		printf("init cost 1 %d \n", init_cost(solu.mat1, solu.dat.size, solutions[i].solution));
		printf("init cost 2 %d \n", init_cost(solu.mat2, solu.dat.size, solutions[i].solution));
		printf("//////////////// \n");
	}
*/


//// OTHER GLOBAL

/*
int number = 0;
int oldSol = 0;

int * oldCost = malloc(sizeof(int) * 2);

while (number <  25) {
	printf("number =  %d \n", number);

	oldSol = sizeSol;
	if (sizeSol > 0) {
		oldCost[0] = solutions[sizeSol - 1].cost_1;
		oldCost[1] = solutions[sizeSol - 1].cost_2;
	}

	for (int i = 0; i < sizeSol; i++) {		
		sizeN = 0;		
		neigh = neighboorhood3 (solutions[i], solu.mat1, solu.mat2, &sizeN, solutions, sizeSol);

		removeGlobal2(neigh, sizeN, &solutions, &sizeSol);
	}

	if (oldSol - sizeSol == 0) {
		if (sameCost (oldCost[0], oldCost[1], solutions[sizeSol - 1].cost_1, solutions[sizeSol - 1].cost_2 ) == 1)
			break;
	}
	if(neigh != NULL){
		free(neigh);
	}

	number++;
}

free(oldCost);


for (int i = 0; i < sizeSol; i++) {
		printf("index i = %d \n", i);
		print_cost(solutions[i]);

		printf("init cost 1 %d \n", init_cost(solu.mat1, solu.dat.size, solutions[i].solution));
		printf("init cost 2 %d \n", init_cost(solu.mat2, solu.dat.size, solutions[i].solution));
		printf("//////////////// \n");
}

/*for (int i =0; i < sizeSol; i++) 
	free(solutions[i].row_1);
	print_tab(solutions[i].solution, 5);

free_matrix(solu.mat1, solu.dat.size);
free_matrix(solu.mat2, solu.dat.size);

//free_tab(solutions, sizeSol, solu.dat.size);

free_mdata(solu.dat);


/*for (int i =0; i < sizeSol; i++) {
	print_tab(solutions[i].solution, 5);
	//free(solutions[i].row_1);
//	free(solutions[i].row_2);
//	free(solutions[i].col_1);
//	free(solutions[i].col_2);
}*/
}
