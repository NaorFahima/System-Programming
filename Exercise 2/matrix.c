/*
 * matrix.c
 *
 *  Created on: 16 בדצמ׳ 2019
 *      Author: נאור פחימה
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "matrix.h"


/*The function void makingMatrixA(float** matrix, float* A, int row, int num) create matrix A */
void makingMatrixA(float** matrix, float* A, int row, int num) {
	for(int colum = 0; colum < num; colum++){
		matrix[row][colum] = A[colum];
	}
}

/*The function void printMatrixA(float** matrix, int num) print matrix */
void printMatrixA(float** matrix, int num) {
	printf("\nMatrix A = \n");
	for(int row = 0; row < num; row++){
		printf("\t");
		for(int colum = 0; colum < num; colum++){
			printf("%.3f ", matrix[row][colum]);
		}
			printf("\n");
	}
}

/*The function void printVectorB(float* bVec, int num) print VectorB */
void printVectorB(float* bVec, int num) {
	printf("\nVector B = \n");
	for(int row = 0; row < num; row++){
			printf("\t");
			printf("%.3f ", bVec[row]);
			printf("\n");
	}
}

/*The function void printVecX(float *vec, int size) print VectorX */
void printVecX(float *vec, int size) {
    printf("\nVector x =\n");
    for (int i = 0; i < size; i++) {
        switch (i) {
        case 0:
            printf("    x = %.3f\n", vec[i]);
            break;
        case 1:
            printf("    y = %.3f\n", vec[i]);
            break;
        case 2:
            printf("    z = %.3f\n", vec[i]);
            break;
        }
    }
}

/*The function void matrixVectorMultiply(Solver *solver, float **mat) Multiply 2 matrix */
void matrixVectorMultiply(Solver *solver, float **mat) {
    float *b = solver->B_Vec;
    float *x = solver->X_Vec;
    int size = solver->count;

    for (int i = 0; i < size; i++) {
        x[i] = 0;
        for (int j = 0; j < size; j++)
            x[i] += mat[i][j] * b[j];
    }
    solver->X_Vec = x;
}

/*The function void freeMemery(float** ptr,int num) free memery of array2D */
void freeMemery(float** ptr,int num){
	 for (int i = 0; i < num; i++) {
		 free(ptr[i]);
	 }
	 free(ptr);
}

/*The function void readEquation(Equation *myEquation ,char *equation, int num) read Equation on put in struct Equation  */
void readEquation(Equation *myEquation ,char *equation, int num) {
    myEquation->A = (float*) malloc(num*sizeof(float));
    myEquation ->count = num;
    char *stringBuf = equation;
    char *subString;
    subString = removeSpaces(stringBuf);

    char variable;
    float number;
    int len = strlen(equation);

    for (int i = 0; i < len; i++) {
        if ((equation[i] == 'x') || (equation[i] == 'y')
                || (equation[i] == 'z')) {
            variable = equation[i];
            switch (variable) {
            case 'x':
                subString = strtok(stringBuf, "x");

                myEquation->A[0] = atof(subString);
                stringBuf = equation + i + 1;
                break;
            case 'y':
                subString = strtok(stringBuf, "y");
                myEquation->A[1] = atof(subString);
                stringBuf = equation + i + 1;
                break;
            case 'z':
                subString = strtok(stringBuf, "z");
                myEquation->A[2] = atof(subString);
                stringBuf = equation + i + 1;
                break;
            default:
            	printf("There has been an error with the multiplication sign.");
            	break;
            }
        } else if (equation[i] == '=') {
        	sscanf((equation + i + 1), "%f", &number);
        	 myEquation->B = number;
        	i = len - 1;
        }
    }
}

/*The function void getInverse(float **inverse, float **mat, int num, float det) calculation matrixInverse */
void getInverse(float **inverse, float **mat, int num, float det) {
    float invDet = 1 / det;
    switch (num) {
   	            case 1:
   	             inverse[0][0] = invDet;
   	                break;
   	            case 2:
   	             inverse[0][0] = mat[1][1] * invDet;
   	                inverse[0][1] = -1 * mat[0][1] * invDet;
   	                inverse[1][0] = -1 * mat[1][0] * invDet;
   	                inverse[1][1] = mat[0][0] * invDet;
   	                break;
   	            case 3:
   	             inverse[0][0] = (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) * invDet;
   	                    inverse[0][1] = -(mat[0][1] * mat[2][2] - mat[0][2] * mat[2][1])* invDet;
   	                    inverse[0][2] = (mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1])* invDet;
   	                    inverse[1][0] = -(mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])* invDet;
   	                    inverse[1][1] = (mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0])* invDet;
   	                    inverse[1][2] = -(mat[0][0] * mat[1][2] - mat[1][0] * mat[0][2])* invDet;
   	                    inverse[2][0] = (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1])* invDet;
   	                    inverse[2][1] = -(mat[0][0] * mat[2][1] - mat[2][0] * mat[0][1])* invDet;
   	                    inverse[2][2] = (mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1])* invDet;
   	                break;
   	            default:
   	            	break;
   	            }
}

/*The function int getDetrmin(float** matrix,int num) calculation detrminanta */
int getDetrmin(float** matrix,int num){
	float minor1,minor2,minor3;
	 switch (num) {
	            case 1:
	            	return matrix[0][0];
	                break;
	            case 2:
	            	return ((matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0]));
	                break;
	            case 3:
	            	minor1 = matrix[0][0]*((matrix[1][1] * matrix[2][2]) - (matrix[2][1] * matrix[1][2]));
	            	minor2 = matrix[0][1]*((matrix[1][0] * matrix[2][2]) - (matrix[2][0] * matrix[1][2]));
	            	minor3 = matrix[0][2]*((matrix[1][0] * matrix[2][1]) - (matrix[2][0] * matrix[1][1]));
	            		return minor1 - minor2 + minor3;
	                break;
	            default:
	            	break;
	            }
}

/*The function char* removeSpaces(char* str) remove spaces from char arrays  */
char* removeSpaces(char* str) {

	int count = 0;
	for(int i=0;str[i];i++) {
		if (str[i] != ' ')
			str[count++] = str[i];
	}
		str[count] = '\0';
		return str;

}

