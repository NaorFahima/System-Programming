#pragma once

#define BITS_IN_CHAR 8 //how many bits are in 1 char
#define BITS_PER_CHAR 4 //how many bits combinations required for the 4 symbols * : . ' '

//get a file name containing a sequence and assign it inside a char * array
char* createSequence(char* fileName);

//get 2 char * arrays sequences and create a compressed sign array made by their comparison
char* createSigns(char* SEQ1, char* SEQ2, int n);

//calculate the difference between the asterisk and colon in the array and return it
int getCount(char* signArray, int length);

//get 2 char * arrays sequences and return the difference between the number of asterisk and colon inside of the sign array made by them
int evaluateDifference(char* SEQ1, char* SEQ2, int n);

//function for debbugging
void printCharAsBinary(char ch);

//gets compressed sign array and decoding it to a normal char array containing the symbols required and returning it
char* createSignsDecode(char* signArray, int length);

//gets an array and printing it to the screen
void printSignArray(char* signArray, int length);