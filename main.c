#include "parser.h"
#include "methods.h"
#include <time.h>

int main(int argc, char** argv) {

	
	//IDEA : do a function with : fileName, number of matrixes; matrix * number, size of matrix in arguments
	int nbMat = 0;
	int sizeMat = 0;	
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	char * testFileName = "res/test.dat";
	int ** mat1 = NULL;
	int ** mat2 = NULL;
	int * sol;
	clock_t t1, t2;
	float temps;

	if (parse(fileName, &sizeMat, &nbMat, &mat1, &mat2) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	
	printf("%d   %d \n", sizeMat, nbMat);


	generate_random_sol(&sol, sizeMat);

	//printf(" value test %d %d \n", mat1[1][999], mat1[999][1]);


/* ///// testing /////

	int * testSol = (int*) malloc(sizeof(int)* sizeMat);
	for (int i = 0; i < sizeMat; i++) {
		testSol[i] = 0;
	}

	t1 = clock();

	init_cost_basic(mat1, sizeMat, sol);

	t2 = clock();
	temps = (float) (t2 - t1) / CLOCKS_PER_SEC;
	printf(" time %f \n", temps);

	t1 = clock();

	init_cost_basic_2(mat1, sizeMat, sol);

	t2 = clock();
	temps = (float) (t2 - t1) / CLOCKS_PER_SEC;
	printf(" b2 time %f \n", temps);

		t1 = clock();


	triang_mat(&mat1, sizeMat);
	init_cost_triang(mat1, sizeMat, sol);

	t2 = clock();
	temps = (float) ((t2 - t1)/ CLOCKS_PER_SEC);
	printf(" reduc time %f  \n", temps);

	

	//print_mat(mat1, sizeMat);
	//printf("basic 2 cost %d  \n", init_cost_basic_2(mat1, sizeMat, testSol));
	//printf("basic  cost %d  \n", init_cost_basic(mat1, sizeMat, testSol));

	triang_mat(&mat1, sizeMat);

	print_mat(mat1, sizeMat);
	printf(" cost %d  \n", init_cost_basic_2(mat1, sizeMat, testSol));


	printf(" cost %d  \n", init_cost_triang(mat1, sizeMat, testSol));

	*/
	////// //////


	//TODO : calculate initial cost => how to save it ?
	//TODO : objective function

	//TODO : calculate additional cost for each solutions



	//TODO : neighboors
	//TODO : save neighboors
	//TODO : method for pareto (to remove, to add ) using objective function



	return 0;
}