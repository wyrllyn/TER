#include "print.h"

int main(int argc, char** argv) {

	// files
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	char * testFileName = "res/test.dat";

	int sizeMat = 0;	

	m_data * solutions;
	int sizeSol = 0;

	//parse
	first_s solu = init(fileName);

	printf("%d \n ", solu.dat.size);

	// temp
	m_data * neigh;
	int sizeN = 0;

//	print_tab(solu.dat.solution, solu.dat.size);

	//print_mat(solu.mat1, solu.dat.size);

	//	print_tab(solu.dat.row_1, solu.dat.size);

//	print_mat(solu.mat2, solu.dat.size);

	print_cost(solu.dat);

	//////////////////////////////////////// trying to do global method /////////////////


	sizeSol++;
	solutions = add_sol(solutions, solu.dat, sizeSol);


	for (int i = 0; i < sizeSol; i++) {
		printf("index i = %d \n", i);
		print_cost(solutions[i]);
	}

	for (int i = 0; i < 2; i++) {
		sizeN = 0;
		neigh = NULL;

		neigh = neighboorhood (solutions[i], solu.mat1, solu.mat2, &sizeN, solutions, sizeSol);

		removeGlobal(neigh, sizeN, &solutions, &sizeSol);
		printf("index %d : SIZE OF NEIGH %d \n", i, sizeN);

		printf("index %d : SIZESOL AFTER REMOVAL %d  \n", i, sizeSol);

		printf("\n ////////////////////////////////////////////// AFTER REMOVE /////////////////////// \n");
		for (int j = 0; j < sizeSol; j++) {
			printf("index j = %d \n", j);
			print_cost(solutions[j]);
		}
		printf("\n /////////////////////// \n");

		solutions = add_neigh(solutions, sizeSol, neigh, sizeN);
		sizeSol += sizeN;
		printf("index %d : SIZESOL AFTER NEIGH ADD %d \n",i, sizeSol);

		printf("\n ////////////////////////////////////////////// solutions /////////////////////// \n");
		for (int j = 0; j < sizeSol; j++) {
			printf("index j = %d \n", j);
			print_cost(solutions[j]);
		}
		printf("\n /////////////////////// \n");
	}

/*	for (int i = 0; i < sizeN; i++) {
			printf("index i = %d \n", i);
//		print_tab(solutions[i].solution, solutions[i].size);
		//print_tab(solutions[i].row_1, solutions[i].size);
			print_cost(neigh[i]);
	}


	///////////////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < sizeSol; i++) {
		printf("index i = %d \n", i);
//		print_tab(solutions[i].solution, solutions[i].size);
		//print_tab(solutions[i].row_1, solutions[i].size);
		print_cost(solutions[i]);
	}
*/





	// idea : function with current sol (init sol first...) => when iteration is done : verification of flags, comparison neigh / currentSol values, add good neigh. Ends with iteration or flag I guess
	// question : how to flag ? 



//  TODO :
	// solutions will become potential acceptable neighboors
	// there will be another tab solutions
	// after neighboors founds => sorted into acceptable_neighboors (if there's dominated solutions => to remove) | get the index of solutions to remove + size + list (int)
	// compare to solutions => 


	//TODO : objective function


	//TODO : neighboors
	//TODO : save neighboors
	//TODO : method for pareto (to remove, to add ) using objective function



	return 0;
}