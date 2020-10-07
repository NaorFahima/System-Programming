/*
 ============================================================================
 Name        : TicketsOrder
 Author      : Naor Fahima
 ID	     : 315783563
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "tickets.h"
#define SIZE 7



/* Create a function void ticketsOrder() that save in array the number of tickets that sold on the week */
void ticketsOrder(){

	int arr[] = {0,0,0,0,0,0,0};
	int day;
	int tickets;
	do {
		printf("Please enter the day:\n");
		scanf("%d",&day);
		if(day<1 || day>SIZE) {
			printf("Not in range\n");
			continue;
		}
		printf("How much tickets sold in this day?\n");
		scanf("%d",&tickets);
		arr[day-1]= tickets + arr[day-1];

	} while (day!=0);
	mostSoldDay(arr);
	leastSoldDay(arr);

}


/* Create a function void mostSoldDay(int* arr) that check which
day was the most sold day*/
void mostSoldDay(int* arr) {
	int mostSoldDay = 0, mostSoldTickets = 0;
	for (int i = 0; i < SIZE; ++i) {
		if (*(arr+i) > mostSoldTickets) {
			mostSoldDay = i;
			mostSoldTickets = *(arr+i);
		}
	}
	printf("The day was sold the most tickets: %d \n they sold %d tickets\n",(mostSoldDay+1),mostSoldTickets);
}

/* Create a function void leastSoldDay(int* arr) that check which
day was the least sold day*/
void leastSoldDay(int* arr) {
	int leastSoldDay = 0 , leastSoldTickets = *arr;
	for (int i = 1; i < SIZE; ++i) {
		if (*(arr+i) < leastSoldTickets) {
			leastSoldDay = i;
			leastSoldTickets = *(arr+i);
		}
	}
	printf("The day was sold the least tickets: %d \n they sold %d tickets\n",(leastSoldDay+1),leastSoldTickets);
}


