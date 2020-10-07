/*
 * struct.c
 *
 *  Created on: 16 בדצמ׳ 2019
 *      Author: נאור פחימה
 */

#pragma once

//struct Equation;
typedef struct
{
	int count;
	float* A;
	float B;

}Equation;


//struct AllEquation;
typedef struct
{
	int cont;
	Equation** eqArr;

}AllEquation;


//struct Solver
typedef struct
{
	int count;
	float** A_Mat;
	float* B_Vec;
	float Detrmin;
	float* X_Vec;
}Solver;
