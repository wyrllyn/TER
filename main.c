#include "parser.h"
#include "methods.h"

int main(int argc, char** argv) {

	
	//IDEA : do a function with : fileName, number of matrixes; matrix * number, size of matrix in arguments
	int nbMat = 0;
	int sizeMat = 0;	
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	char * testFileName = "res/test.dat";
	int ** mat1 = NULL;
	int ** mat2 = NULL;
	int * sol;

	if (parse(fileName, &sizeMat, &nbMat, &mat1, &mat2) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	
	printf("%d   %d \n", sizeMat, nbMat);
//	print_mat(mat1, sizeMat);
//	print_mat(mat2, sizeMat);

	generate_random_sol(&sol, sizeMat);
	for (int i = 0; i<sizeMat; i++) {
		printf("\n %d", sol[i]);
	}
	printf("\n");

	
	////// //////


	//TODO : calculate initial cost => how to save it ?
	//TODO : objective function

	//TODO : calculate additional cost for each solutions



	//TODO : neighboors
	//TODO : save neighboors
	//TODO : method for pareto (to remove, to add ) using objective function



	return 0;
}