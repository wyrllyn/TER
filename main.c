#include "methods.h"


int main(int argc, char** argv) {

	int max = 50000;
	// files
	char* fileName5 = "res/mubqp_0.5_2_4000_0.8_0.dat";

	char * fileName = "res/mubqp_0.0_2_1000_0.8_0.dat";

	char* fileName3 = "res/mubqp_0.5_2_1000_0.8_0.dat";

	char* fileName2 = "res/mubqp_0.0_2_1000_1.0_0.dat";	

	char* fileName9 ="res/mubqp_-0.5_2_1000_0.8_0.dat";

	char * testFileName = "res/test.dat";



	clock_t begin, end;
	double time_spent;
	begin = clock();

	//global4(fileName3);
	global_hypervolume2(fileName3);

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("EXEC TIME : %f \n", time_spent );

	return 0;
}
