#include "methods.h"

void print_mat(int ** mat, int size) {
	int i = 0;
	int j = 0;
	//order col 1, line 1 col 2, line 2
	for (i = 0; i < size; i++){
		printf("\n");
		for (j = 0; j < size; j++){ //
			printf("%d ", mat[j][i]);
		}
	}
	printf("\n");
}

void print_tab(int* tab, int size) {
	for (int i = 0; i<size; i++) {
		printf("\n %d", tab[i]);
	}
	printf("\n");
}

void generate_random_sol(int ** tab, int size){
	int i = 0;
	*tab = malloc(sizeof(int) * size);
	for (i = 0; i < size; i++) {
		(*tab)[i] = rand() % 2;
	}
}