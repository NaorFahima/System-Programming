/*
 * matrix.h
 *
 *  Created on: 16 בדצמ׳ 2019
 *      Author: נאור פחימה
 */
#pragma once

/*The function void getInverse(float **inverse, float **mat, int num, float det) calculation matrixInverse */
void getInverse(float **inverse, float **mat, int num, float det) ;

/*The function int getDetrmin(float** matrix,int num) calculation detrminanta */
int getDetrmin(float** matrix,int num);

/*The function void makingMatrixA(float** matrix, float* A, int row, int num) create matrix A */
void makingMatrixA(float** matrix, float* A, int row, int num);

/*The function void printMatrixA(float** matrix, int num) print matrix */
void printMatrixA(float** matrix, int num);

/*The function void printVectorB(float* bVec, int num) print VectorB */
void printVectorB(float* bVec, int num);

/*The function void printVecX(float *vec, int size) print VectorX */
void printVecX(float *vec, int size);

/*The function void matrixVectorMultiply(Solver *solver, float **mat) Multiply 2 matrix */
void matrixVectorMultiply(Solver *solver, float **mat);

/*The function void readEquation(Equation *myEquation ,char *equation, int num) read Equation on put in struct Equation  */
void readEquation(Equation *myEquation ,char *equation, int num);

/*The function void freeMemery(float** ptr,int num) free memery of array2D */
void freeMemery(float** ptr,int num);

/*The function char* removeSpaces(char* str) remove spaces from char arrays  */
char* removeSpaces(char* str);


