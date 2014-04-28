#include "parser.h"
#include "methods.h"

int main(int argc, char** argv) {

	
	//IDEA : do a function with : fileName, number of matrixes; matrix * number, size of matrix in arguments
	int sizeMat = 0;	

	// files
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	char * testFileName = "res/test.dat";
	// matrix
/*	int ** mat1 = NULL;
	int ** mat2 = NULL;
	// solution
	int * sol;
	// rows & columns
	int * row1;
	int * row2;
	int* col1;
	int * col2;

	if (parse(testFileName, &sizeMat, &mat1, &mat2) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	
	printf("%d  \n", sizeMat);

	generate_random_sol(&sol, sizeMat);*/

	////// testing init methods
	first_s solu = init(fileName);

	printf("%d \n ", solu.dat.size);

//	print_mat(solu.mat1, solu.dat.size);
//	print_tab(solu.dat.solution, solu.dat.size);
	print_cost(solu.dat);

/*
	// testing
	for (int i = 0; i < sizeMat; i++) {
		printf("test \n");
		sol[i] = 0;
	}


	sol[0] = 1;
	sol[2] = 1;

	printf(" cost 1 is : %d \n ", init_cost(mat1, sizeMat, sol));
	printf(" cost 2 is : %d \n ", init_cost(mat2, sizeMat, sol));


	print_mat(mat2, sizeMat);


	printf(" cost 1 is : %d \n ", init_cost(mat1, sizeMat, sol));


	init_row_value(&row1, mat1, sizeMat, sol);
	init_col_value(&col1, mat1, sizeMat, sol);

	init_row_value(&row2, mat2, sizeMat, sol);
	init_col_value(&col2, mat2, sizeMat, sol);


	print_tab(row1, sizeMat);
	print_tab(col1, sizeMat);

	update_row(sizeMat, &row1, mat1, 2, -1 );
	update_col(sizeMat, &col1, mat1, 2, -1 );


	print_tab(row1, sizeMat);
	print_tab(col1, sizeMat);

*/

	//TODO : objective function


	//TODO : neighboors
	//TODO : save neighboors
	//TODO : method for pareto (to remove, to add ) using objective function



	return 0;
}