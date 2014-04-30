#include "print.h"

int main(int argc, char** argv) {

	int sizeMat = 0;	

	// files
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	char * testFileName = "res/test.dat";

	m_data * solutions;
	int sizeSol = 0;
	first_s solu = init(testFileName);

	printf("%d \n ", solu.dat.size);

	// temp
	m_data * neigh;
	int sizeN = 0;

//	print_tab(solu.dat.solution, solu.dat.size);

	//print_mat(solu.mat1, solu.dat.size);

	//	print_tab(solu.dat.row_1, solu.dat.size);

//	print_mat(solu.mat2, solu.dat.size);

	print_cost(solu.dat);

	neigh = neighboorhood (solu.dat, solu.mat1, solu.mat2, &sizeN);

	for (int i = 0; i < sizeN; i++) {
		printf("index i = %d \n", i);
//		print_tab(solutions[i].solution, solutions[i].size);
		//print_tab(solutions[i].row_1, solutions[i].size);
		print_cost(neigh[i]);
	}

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