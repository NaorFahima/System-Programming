/*
 ============================================================================
 Name        : main.c
 Author      : Naor Fahima
 ID          : 315783563
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "matrix.h"

#define SIZE 80




void main(void) {

	int num;
	char dummy;
	char userEq[SIZE];
	int endLoop=-1;
	float **invMatrix;
	AllEquation allEquation;
	Solver sol;

	memset(userEq, 0, sizeof(userEq)); // put in the array 0;

	do {
		printf("Number of equations (1-3): ");
		scanf("%d",&num); // read number
		if (num<=3 && num>0) {
			endLoop=0;

			// make memery
			allEquation.eqArr = (Equation **) malloc(num*sizeof(Equation*));
			sol.A_Mat = (float**) malloc(num*sizeof(float*));
			sol.B_Vec = (float*) malloc(num*sizeof(float));
			sol.X_Vec = (float*) malloc(num*sizeof(float));
			invMatrix = (float**)malloc(num*sizeof(float*));
			//


			allEquation.cont = num;
			sol.count = num;
			scanf("%c", &dummy);    // clean the buffer
			for (int i = 0; i < num; i++) {
				sol.A_Mat[i] = (float*) malloc(3 * sizeof(float)); // make memery
				invMatrix[i] = (float*) malloc(3 * sizeof(float));
				allEquation.eqArr[i] = (Equation *) malloc(sizeof(Equation));
				printf("Enter equation %d:",i+1);
				gets(userEq); // read equation
				readEquation(allEquation.eqArr[i],userEq,num);
				sol.B_Vec[i] = allEquation.eqArr[i]->B;
				makingMatrixA(sol.A_Mat,allEquation.eqArr[i]->A,i,allEquation.eqArr[i]->count);
			}
			printMatrixA(sol.A_Mat,num); // print matrix
			sol.Detrmin = getDetrmin(sol.A_Mat,num); // calculation detrminanta
			printf("\nMatrix A determinant = %.3f\n",sol.Detrmin);
			printVectorB(sol.B_Vec,num); // print vector

			if (sol.Detrmin==0) {
				printf("There is no single solution for that system of equations.");
			}else {
				getInverse(invMatrix, sol.A_Mat, sol.count, sol.Detrmin); // calculation matrixInverse
				matrixVectorMultiply(&sol, invMatrix);
				printVecX(sol.X_Vec, sol.count); // print vector X
			}

			// free the memery
			freeMemery(sol.A_Mat,num);
			freeMemery(invMatrix,num);
			free(sol.B_Vec);
			free(sol.X_Vec);
		}else {
			printf("You have to choose a number between (1-3)!!\n");
		}
	} while (endLoop!=0);
}








