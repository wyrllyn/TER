#include "parser.h"
#include "methods.h"

int main(int argc, char** argv) {

	
	//IDEA : do a function with : fileName, number of matrixes; matrix * number, size of matrix in arguments
	int sizeMat = 0;	

	// files
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	char * testFileName = "res/test.dat";

	first_s solu = init(testFileName);

	printf("%d \n ", solu.dat.size);

	print_tab(solu.dat.solution, solu.dat.size);

	print_mat(solu.mat1, solu.dat.size);

	print_mat(solu.mat2, solu.dat.size);

	print_cost(solu.dat);
	int * tmp;

	for (int i = 0; i < solu.dat.size; i++) {
		tmp = calculate_costs(solu.dat, solu.mat1, solu.mat2, i);
		printf("%d :  %d %d \n", i, tmp[0], tmp[1]);
	}

	//TODO : objective function


	//TODO : neighboors
	//TODO : save neighboors
	//TODO : method for pareto (to remove, to add ) using objective function



	return 0;
}