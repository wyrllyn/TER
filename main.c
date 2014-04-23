#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

#define MAX_SIZE 200

int main(int argc, char** argv) {

	
	FILE * file = NULL;	
	// TODO : argument string for file name //
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	char str[MAX_SIZE] = "";

	/// PARSE ///
	file = fopen(fileName, "r");

	int i = 0;

	if (file != NULL) {

		// TODO: read
		while(fgets(str, MAX_SIZE, file) != NULL) {

			//ou fscanf ? 
			printf(" read %d \n", i);
			i++;
			// get the N
			// get size of matrix
			// set N matrix
			//fill N matrix 
		}

		fclose(file);
	}
	else {
		printf("Could not open the file %s \n", fileName);
		return EXIT_FAILURE;
	}
	////// //////


	printf("end");
	//TODO : generate a random solution 

	//TODO : objective function

	//TODO : neighboors

	//TODO : save neighboors

	//TODO : method for pareto (to remove, to add ) using objective function



	return 0;
}