#include "parser.h"
#include "methods.h"

int main(int argc, char** argv) {

	
	//IDEA : do a function with : fileName, number of matrixes; matrix * number, size of matrix in arguments
	int nbMat = 0;
	int sizeMat = 0;	

	// files
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	char * testFileName = "res/test.dat";
	// matrix
	int ** mat1 = NULL;
	int ** mat2 = NULL;
	// solution
	int * sol;
	// rows & columns
	int * row1;
	int * row2;
	int* col1;
	int * col2;

	if (parse(testFileName, &sizeMat, &nbMat, &mat1, &mat2) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	
	printf("%d   %d \n", sizeMat, nbMat);

	generate_random_sol(&sol, sizeMat);

	// testing
	for (int i = 0; i < sizeMat; i++) {
		printf("test \n");
		sol[i] = 0;
	}


	sol[0] = 1;
	sol[2] = 1;

	printf(" cost 1 is : %d \n ", init_cost(mat1, sizeMat, sol));
	printf(" cost 2 is : %d \n ", init_cost(mat2, sizeMat, sol));

	print_mat(mat1, sizeMat);
	print_mat(mat2, sizeMat);


	printf(" cost 1 is : %d \n ", init_cost(mat1, sizeMat, sol));


	init_row_value(&row1, mat1, sizeMat, sol);
	init_col_value(&col1, mat1, sizeMat, sol);

	init_row_value(&row2, mat2, sizeMat, sol);
	init_col_value(&col2, mat2, sizeMat, sol);

	printf("if 0 is removed %d \n", delta_index(mat1, row1, col1, sol, 0));



	// end of testin'




	//TODO : calculate initial cost => how to save it ?
	//TODO : objective function

	//TODO : calculate additional cost for each solutions


	//TODO : neighboors
	//TODO : save neighboors
	//TODO : method for pareto (to remove, to add ) using objective function



	return 0;
}