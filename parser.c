#include "parser.h"




int parse(char* fileName, int* sizeMat, int* nbMat, int*** mat1, int*** mat2) {
	FILE * file = NULL;	
	char str[MAX_SIZE] = "";
	file = fopen(fileName, "r");
	char* tok;
	int nbr = 0;

	int col = 0;
	int line = 0;


	/// PARSE ///
	if (file != NULL) {

		// TODO: read
		while(fgets(str, MAX_SIZE, file) != NULL) {
			// used to ignore commentaries
			if (str[0] != 'c') {
				if (str[0] == 'p'){
					//// test

					tok = str;
					int temp = 4;
					while ((tok = strtok(tok, " ")) != NULL){
    			   		//printf("<<%s>>\n", tok);
    			   		temp++;
    			   		if ( strcmp( tok, "MUBQP") == 0 ){
    			   			temp = 0;
    			   		}
    			   		if (temp == 2)
    			   			*nbMat = atoi(tok);
    			   		else if (temp == 3) {
    			   			*sizeMat = atoi(tok);
    			   			*mat1 = (int**)malloc(sizeof(int*) * (*sizeMat));
    			   			*mat2 = (int**)malloc(sizeof(int*) * (*sizeMat));
    			   			for ( col = 0; col < *sizeMat; col++) {
    			   				(*mat1)[col] = malloc(sizeof(int) * (*sizeMat));
								(*mat2)[col] = malloc(sizeof(int) * (*sizeMat));
    			   			}
    			   			col = 0;
    			   		}
     					tok = NULL;
 				   }			
				}
				else {
					tok = str;
				//	printf("\n str : %s", str);
					tok = strtok(tok, " ");

				//	printf("\n\t tok 1  %d", atoi(tok));
					(*mat1)[col][line] = atoi(tok);
					tok = NULL;
					tok = strtok(tok, " ");
				//	printf("\n\t tok 2  %d", atoi(tok));
					(*mat2)[col][line] = atoi(tok);

					// variables
					col++;
					if (col == *sizeMat && line != *sizeMat) {
						col = 0;
						line++;
					}
				}
			}
		}

		fclose(file);
	}
	else {
		printf("Could not open the file %s \n", fileName);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}