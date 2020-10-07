/*
 ============================================================================
 Name        : checkSudoku.c
 Author      : Naor Fahima
 ID	     : 315783563
 ============================================================================
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 25


/* Create a function void sudokuGame() that chack if the sudoku that user input is valid */
void sudokuGame(){

	int size;

	do{
	printf("Please input the size of the sudoku (4,9,16,25):\n",size);
	scanf("%d" ,&size);
	if (!(size==4 || size==9 || size==16 || size==25)) {
		printf("You have to choose a number of options\n");
	}
	} while(!(size==4 || size==9 || size==16 || size==25));

	int helpArr[size];
	int validSudoku = 1;
	int arr[size][size];
	int* p = arr;

	for ( int i = 0;  i< size*size; i++) {
		printf("Please input number , indux %d:\n",i);
		scanf("%d",(p+i));
	}
	showMatrix(arr,size);

	restArrayHelp(helpArr,size);

	int sum=checkSum(arr,size);
	checkBoard(arr,size,sum);

	if (checkRowMatrix(arr,helpArr,size) +checkColumnMatrix(arr,helpArr,size)+validSudoku == 3 ) {
		printf("\nSudoku is valid");
	} else {
		printf("\nSudoku is not valid");
	}
}

/* Create a function int checkBoard(int *arr,int length,int sum) that chack board*/
int checkBoard(int *arr,int length,int sum){ 
    int sR = (int) sqrt((double) length);
    for(int j = 0; j<sR; j++){
        
        for (int i = 0; i<sR;i++){
            
            if (checksquares(arr,sR,sum) == 1){
            return 1;
            }
            arr+=sR;
        }
        arr = arr - sR;
        arr = arr + ((length*sR) - (length - sR));
    }
    return 0;
}

/* Create a function int checksquares(int *arr,int length,int sum) that chack sudoku squares*/
int checksquares(int *arr,int length,int sum){
     int checkSum = 0;
    for(int i = 0 ; i<length ; i++){
        for(int j = 0; j<length; j++){
            checkSum+=*arr;
            arr++;
        }
        arr+=(length*(length - 1 ));
    }
    if (checkSum != sum){
        return 1;
    }
    return 0;
}

/* Create a function int checkColumnMatrix(int* arr ,int* helpArr ,int size) that chack if the sudoku columns is valid */
int checkColumnMatrix(int* arr ,int* helpArr ,int size){
	int counter = 0;
	int check = 0;
	int colum = 1;
	for (int* p = arr; p < arr + size*size; p = p+size) {
		if (*p <=size) {
			(*(helpArr+*p-1))++;
		} else {
			return -1;
		}
		counter++;
		if (counter == size) {
		    p = arr+colum-size;
			colum++;
			check = check + checkArrayHelp(helpArr,size);
			restArrayHelp(helpArr,size);
			counter = 0;
		}
	}
	if (check == size) {
		return 1;
	}else {
		return -1;
	}
}

/* Create a function int checkRowMatrix(int* arr ,int* helpArr ,int size) that chack if the sudoku rows is valid */
int checkRowMatrix(int* arr ,int* helpArr ,int size){
	int counter = 0;
	int check = 0;
	for (int* p = arr; p < arr + size*size; p++) {
		if (*p <=size) {
			(*(helpArr+*p-1))++;
		} else {
			return -1;
		}
		counter++;
		if (counter == size) {
			check = check + checkArrayHelp(helpArr,size);
			restArrayHelp(helpArr,size);
			counter = 0;
		}
	}
	if (check == size) {
		return 1;
	}else {
		return -1;
	}

}

/* Create a function int checkSum(int* arr,int size) that chack what sum of valid sudoku */
int checkSum(int* arr,int size){//give the sum of array
	int sum=0;
	for (int* p = arr;  p <arr+ size;  p++) {
		sum=sum+*p;
	}
	return sum;
}

/* Create a function void restArrayHelp(int* helpArr , int size) that input zero in array help */
void restArrayHelp(int* helpArr , int size){
	for (int* p = helpArr; p < helpArr + size; p++) {
		*p = 0;
	}
}


/* Create a function int checkArrayHelp(int* helpArr , int size) that check if the array helper is valid */
int checkArrayHelp(int* helpArr , int size){
	for (int* p = helpArr; p < helpArr + size; p++) {
			if (*p != 1 ) {
				return -1;
			}
		}
	return 1;
}

/* Create a function void showMatrix(int* arr , int size) that print the sudoku (matrix) */
void showMatrix(int* arr , int size){
	int counter = 0;
	for (int* p = arr; p < arr + size*size; p++) {
		if (counter == size) {
			printf("\n");
			counter = 0;
		}
		printf("%d " , *p);
		counter++;
		}
}


