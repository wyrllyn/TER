#include "parser.h"

int main(int argc, char** argv) {

	
	//IDEA : do a function with : fileName, number of matrixes; matrix * number, size of matrix in arguments
	int nbMat = 0;
	int sizeMat = 0;	
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	int ** mat1 = NULL;
	int ** mat2 = NULL;
	int i = 0;
	int j = 0;

	parse("res/test.dat", &sizeMat, &nbMat, &mat1, &mat2);
	
	printf(" \n %d   %d \n", sizeMat, nbMat);

	
	////// //////

	if (mat1 == NULL) {
		printf("this is shit \n");
	}

	//ordre parsage col 1, ligne 1 col 2, ligne 2

	for (i = 0; i < sizeMat; i++){
		printf("\n");
		for (j = 0; j < sizeMat; j++){ //
			printf("%d ", mat1[j][i]);
		}
	}


	printf("\n end");
	//TODO : generate a random solution 

	//TODO : objective function

	//TODO : neighboors

	//TODO : save neighboors

	//TODO : method for pareto (to remove, to add ) using objective function



	return 0;
}