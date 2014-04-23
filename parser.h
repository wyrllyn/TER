#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 200

int parse(char* fileName, int* sizeMat, int* nbMat, int*** mat1, int*** mat2);

#endif