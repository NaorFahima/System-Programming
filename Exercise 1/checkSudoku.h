/*
 ============================================================================
 Name        : checkSudoko.h
 Author      : Naor Fahima
 ID	     : 315783563
 ============================================================================
 */


/* Create a function void sudokuGame() that chack if the sudoku that user input is valid */
void sudokuGame();


/* Create a function int checkColumnMatrix(int* arr ,int* helpArr ,int size) that chack if the sudoku columns is valid */
int checkColumnMatrix(int* arr ,int* helpArr ,int size);


/* Create a function int checkRowMatrix(int* arr ,int* helpArr ,int size) that chack if the sudoku rows is valid */
int checkRowMatrix(int* arr ,int* helpArr ,int size);

/* Create a function int checkSum(int* arr,int size) that chack what sum of valid sudoku */
int checkSum(int* arr,int size);


/* Create a function void restArrayHelp(int* helpArr , int size) that input zero in array help */
void restArrayHelp(int* helpArr , int size);

/* Create a function int checkArrayHelp(int* helpArr , int size) that check if the array helper is valid */
int checkArrayHelp(int* helpArr , int size);


/* Create a function void showMatrix(int* arr , int size) that print the sudoku (matrix) */
void showMatrix(int* arr , int size);

/* Create a function int checkBoard(int *arr,int length,int sum) that chack board*/
int checkBoard(int *arr,int length,int sum);


/* Create a function int checksquares(int *arr,int length,int sum) that chack sudoku squares*/
int checksquares(int *arr,int length,int sum);