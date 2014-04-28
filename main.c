#include "print.h"

int main(int argc, char** argv) {

	
	//IDEA : do a function with : fileName, number of matrixes; matrix * number, size of matrix in arguments
	int sizeMat = 0;	

	// files
	char * fileName = "res/mubqp_0.0_2_1000_0.4_0.dat";
	char * testFileName = "res/test.dat";

	first_s solu = init(testFileName);

	printf("%d \n ", solu.dat.size);

//	print_tab(solu.dat.solution, solu.dat.size);

	print_mat(solu.mat1, solu.dat.size);

	//	print_tab(solu.dat.row_1, solu.dat.size);

	print_mat(solu.mat2, solu.dat.size);

	print_cost(solu.dat);
	int * tmp;
	m_data data_tmp;

	m_data * solutions;
	int sizeSol = 0;

// this test adds every solution 
	for (int i = 0; i < solu.dat.size; i++) {
		tmp = calculate_costs(solu.dat, solu.mat1, solu.mat2, i);
		data_tmp = to_m_data(i, solu.dat, tmp, solu.mat1, solu.mat2);
		sizeSol++;
		solutions = add_sol(solutions, data_tmp, sizeSol);
	}

	for (int i = 0; i < sizeSol; i++) {
		printf("index i = %d \n", i);
		print_tab(solutions[i].solution, solutions[i].size);
		print_tab(solutions[i].row_1, solutions[i].size);
		print_cost(solutions[i]);
	}

	//print_tab(solu.dat.row_1, solu.dat.size); */

	//TODO : objective function


	//TODO : neighboors
	//TODO : save neighboors
	//TODO : method for pareto (to remove, to add ) using objective function



	return 0;
}