/*
 ============================================================================
 Name        : checkNumbers.c
 Author      : Naor Fahima
 ID	     : 315783563
 ============================================================================
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "checkNumbers.h"

#define SIZE 10

static int Digit_1=0;
static int Digit_2=0;
static int Digit_3=0;
static int check =0;



/* Create a function void checkNumbers() that chack array and say how many number have one , two or three digit and if the numbers in the range   */
void checkNumbers(){

	int min = rand()%10 +1 , max = rand()%500 +1;
		int size;
		printf("Please input size of the array (between 1 - %d):\n" , SIZE);
		scanf("%d", &size);
		if (size > SIZE) {
			size = SIZE;
		}
		int arr[size];
		inputNumbers(arr,size);
		checkNumberRange(arr,size,min,max);
		checkOneDigit(arr,size,min,max);
		checkTwoDigit(arr,size,min,max);
		checkThreeDigit(arr,size,min,max);
		printf("Min: %d \nMax: %d \nSize: %d \n" , min , max,size);
		if (check == 0) {
			printf("All numbers are OK!  %d -> 1-digit numbers,  %d -> 2-digit numbers, %d -> 3-digit numbers.",Digit_1,Digit_2,Digit_3);
		} else {
			printf("NOT all numbers are OK!  %d -> 1-digit numbers,  %d -> 2-digit numbers, %d -> 3-digit numbers.",Digit_1,Digit_2,Digit_3);
		}

}


/* Create a function void checkNumberRange(int* arr , int size , int min ,int max) that chack
 if in the array has number out of range*/
void checkNumberRange(int* arr , int size , int min ,int max){
		for (int i = 0; i < size; i++) {
			if(*(arr+i)<min || *(arr+i)>max) {
				check =  -1;
			}
		}
}

/* Create a function void checkOneDigit(iint* arr , int size , int min ,int max) that chack
 how many numbers have one digit*/
void checkOneDigit(int* arr , int size , int min ,int max){
		for (int i = 0; i < size; i++) {
			if(*(arr+i)>=0 && *(arr+i)<=9) {
				Digit_1++;
			}
		}
}

/* Create a function void checkTwoDigit(int* arr , int size , int min ,int max) that chack
 how many numbers have two digit*/
void checkTwoDigit(int* arr , int size , int min ,int max){
		for (int i = 0; i < size; i++) {
			if(*(arr+i)>=10 && *(arr+i)<=99) {
				Digit_2++;
			}
		}
}

/* Create a function void checkThreeDigit(int* arr , int size , int min ,int max) that chack
 how many numbers have three digit*/
void checkThreeDigit(int* arr , int size , int min ,int max){
		for (int i = 0; i < size; i++) {
			if(*(arr+i)>=100 && *(arr+i)<=999) {
				Digit_3++;
			}
		}
}

/* Create a function void inputNumbers (int* arr , int size) that input numbers
 from the user to the array*/
void inputNumbers (int* arr, int size) {
		for (int i = 0; i < size; i++) {
				printf("Please enter the array number , in index : %d \n" , i);
				scanf("%d" ,(arr+i));
			}
		printf("\n");
}

