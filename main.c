#include "print.h"

int main(int argc, char** argv) {

	// files
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	char * testFileName = "res/test.dat";

	int sizeMat = 0;	

	m_data * solutions;
	int sizeSol = 0;

	//parse
	first_s solu = init(testFileName);
	// temp
	m_data * neigh;
	int sizeN = 0;


	sizeSol++;
	solutions = add_sol(solutions, init_m_data(solu.dat), sizeSol);

	printf("INITIAL COSTS : \n");
	print_cost(solutions[0]);

		printf("size %d \n ", solu.dat.size);

/*
	//////////////////////////////////////// Global method /////////////////
	for (int i = 0; i < sizeSol; i++) {
		printf("%d - %d \n", i, sizeSol);
		sizeN = 0;
		

		neigh = neighboorhood (solutions[i], solu.mat1, solu.mat2, &sizeN, solutions, sizeSol);
		
		solutions =  add_neigh(solutions, sizeSol, neigh, sizeN);
		free(neigh);
		sizeSol += sizeN;		

	}

	printf("done \n");
	for (int i = 0; i < sizeSol; i++) {
		printf("index i = %d \n", i);
		print_cost(solutions[i]);
		//printf("init cost 1 %d \n", init_cost(solu.mat1, solu.dat.size, solutions[i].solution));
		//printf("init cost 2 %d \n", init_cost(solu.mat2, solu.dat.size, solutions[i].solution));
		printf("////////////////");
	}



//// OLD ONE
/*	for (int i = 0; i < sizeSol; i++) {
		sizeN = 0;
		neigh = NULL;
		
		neigh = neighboorhood (solutions[i], solu.mat1, solu.mat2, &sizeN, solutions, sizeSol);
		removeGlobal(neigh, sizeN, &solutions, &sizeSol);
		solutions = add_neigh(solutions, sizeSol, neigh, sizeN);
		sizeSol += sizeN;
	}
*/

	
int number = 0;
int oldSol = 0;

int* oldBits = NULL;

while (number <  3) {
	printf("number =  %d \n", number);
	oldSol = sizeSol;
	oldBits = copy(solutions[sizeSol - 1].solution, solu.dat.size);

	for (int i = 0; i < sizeSol; i++) {		
		sizeN = 0;		
		neigh = neighboorhood (solutions[i], solu.mat1, solu.mat2, &sizeN, solutions, sizeSol);

		removeGlobal2(neigh, sizeN, &solutions, &sizeSol);
	}

	number++;
	if (oldSol - sizeSol == 0) {
		if (isTheSame (oldBits, solutions[sizeSol - 1].solution, solu.dat.size ) == 1)
			break;
	}
}

for (int i = 0; i < sizeSol; i++) {
		printf("index i = %d \n", i);
		print_cost(solutions[i]);
		//printf("init cost 1 %d \n", init_cost(solu.mat1, solu.dat.size, solutions[i].solution));
		//printf("init cost 2 %d \n", init_cost(solu.mat2, solu.dat.size, solutions[i].solution));
		printf("//////////////// \n");
}


free_matrix(solu.mat1, solu.dat.size);
free_matrix(solu.mat2, solu.dat.size);
free_mdata(solu.dat);

for (int i = 0; i < sizeSol; i++) {
	free_mdata(solutions[i]);
}

for (int i = 0; i < sizeN; i++) {
	free_mdata(neigh[i]);
}
free(solutions);
free(neigh);



	// idea : function with current sol (init sol first...) => when iteration is done : verification of flags, comparison neigh / currentSol values, add good neigh. Ends with iteration or flag I guess
	// question : how to flag ? 



//  TODO :
	// solutions will become potential acceptable neighboors
	// there will be another tab solutions
	// after neighboors founds => sorted into acceptable_neighboors (if there's dominated solutions => to remove) | get the index of solutions to remove + size + list (int)
	// compare to solutions => 

	return 0;
}