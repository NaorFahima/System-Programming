#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "func.h"


char* aminAcidClose[] = { "STA", "NEQK", "NDEQ", "NHQK", "QHRK", "MILV", "MILF", "HY", "FYW" }; //The Close Amin Acid Table
char* aminAcidSimilar[] = { "CSA", "ATV", "SAG", "STNK", "STPA", "SGND", "SNDEQK", "NDEQHK", "NEQHRK", "FVLIM", "HFY" }; //The Similar Amin Acid Table

char* createSequence(char* fileName) {

	FILE* f = fopen(fileName, "r"); //open the sequence file
	if (f == NULL) {
		printf("File cannot be open");
		return NULL;
	}
	fseek(f, 0L, SEEK_END); // takes the file pointer to the end of the file
	int size = ftell(f); //save the size of the file (how many chars)

	char* seq = malloc(sizeof(char) * size); //assign a memory for the sequence
	if (seq == NULL) {
		printf("No memory for the Seq!");
		return NULL;
	}

	rewind(f); //take the file pointer back to the start of the file

	fgets(seq, size, f); //saves the content of the file to the seq pointer
	fclose(f);
	return seq;
}

//function for debbugging
void printCharAsBinary(char ch) {
	int i;
	unsigned char temp;
	for (i = 0; i < BITS_IN_CHAR; i++)
	{
		temp = ch << i;
		temp = temp >> 7;
		printf("%d", temp);
	}
	printf("\n");
}

char setBit(unsigned char ch, int index, int value) {
	unsigned char mask = 1; //makes a mask 00000001
	unsigned char result;
	mask <<= index; //makes the mask to be the correct byte for the current index

	if (value == 1)
		result = ch | mask; //if the value needed to set is 1 than do OR
	else
	{
		mask = ~mask; //bitwise complement the current byte (changes 0 to 1 and 1 to 0)
		result = ch & mask; //if the value needed to set is 0 than do AND
	}
	return result;
}

char getBit(unsigned char ch, int index) {
	unsigned char mask = 1; //makes a mask 00000001
	unsigned char result;
	mask <<= index; //makes the mask to be the correct byte for the current index
	result = ch & mask;  // makes AND on the 2 bytes

	if (result == '\0') //checks which bite to return (0 or 1)
		return '0';
	else
		return '1';
}

char* createSigns(char* SEQ1, char* SEQ2, int n) {
	char* signArray = (char*)malloc((strlen(SEQ2) * sizeof(char) * BITS_IN_CHAR) / BITS_PER_CHAR); //assign the memory for the sign array 
	if (signArray == NULL) {
		printf("No memory for the signArray!");
		return NULL;
	}
	int currentBit = 0;
	int found = 0;
	for (int i = 0; i < strlen(SEQ2); i++) {
			if (SEQ1[n + i] == SEQ2[i]) { //if the char in the 2 sequences is the same then
				//01 = *
				signArray[currentBit / 8] = setBit(signArray[currentBit / 8], currentBit % 8, 1); //assign the first bit in the current byte
				signArray[currentBit / 8] = setBit(signArray[currentBit / 8], (currentBit % 8) + 1, 0); //assign the second bit in the current byte
				currentBit += 2; //jump to the next 2 bits
			}
			else {
					for (int j = 0; j < sizeof(aminAcidClose) / sizeof(aminAcidClose[0]); j++) {
						//check if the char from SEQ1 and the char from SEQ2 are inside of any Close amin acid array combination 
						if (strchr(aminAcidClose[j], SEQ1[n + i]) != NULL && 
							strchr(aminAcidClose[j], SEQ2[i]) != NULL) {
							//11 = :
							signArray[currentBit / 8] = setBit(signArray[currentBit / 8], currentBit % 8, 1); //assign the first bit in the current byte
							signArray[currentBit / 8] = setBit(signArray[currentBit / 8], (currentBit % 8) + 1, 1); //assign the second bit in the current byte
							currentBit += 2; //jump to the next 2 bits
							found++;
							break;
						}
					}
					if (found == 0) { //if match hasn't been found then check here
						for (int j = 0; j < sizeof(aminAcidSimilar) / sizeof(aminAcidSimilar[0]); j++) {
							//check if the char from SEQ1 and the char from SEQ2 are inside of any Similar amin acid array combination 
							if (strchr(aminAcidSimilar[j], SEQ1[n + i]) != NULL &&
								strchr(aminAcidSimilar[j], SEQ2[i]) != NULL) {
								//10 = .
								signArray[currentBit / 8] = setBit(signArray[currentBit / 8], currentBit % 8, 0); //assign the first bit in the current byte
								signArray[currentBit / 8] = setBit(signArray[currentBit / 8], (currentBit % 8) + 1, 1); //assign the second bit in the current byte
								currentBit += 2;  //jump to the next 2 bits
								found++;
								break;
							}
						}
					}

					if (found == 0) { //if match hasn't been found then check here
						//00 = ' '
						signArray[currentBit / 8] = setBit(signArray[currentBit / 8], currentBit % 8, 0); //assign the first bit in the current byte
						signArray[currentBit / 8] = setBit(signArray[currentBit / 8], (currentBit % 8) + 1, 0); //assign the second bit in the current byte
						currentBit += 2; //jump to the next 2 bits
					}
					found = 0; //reset the found variable for the next loop
			}
	}
	return signArray;
}

char * createSignsDecode(char* signArray, int length) {
	char* dSignArray = (char*)malloc(length * sizeof(char)); //assign the memory for the decoded sign array 
	if (dSignArray == NULL) {
		printf("No memory for the dSignArray!");
		return NULL;
	}
	int currentBit = 0;
	for (int i = 0; i < length; i++) {
		char first =  getBit(signArray[currentBit / 8], currentBit % 8); //get the first bit in the current byte
		char second = getBit(signArray[currentBit / 8], (currentBit+1) % 8); //get the second bit in the current byte
		if (first == '1' && second == '0') { 
			dSignArray[i] = '*'; //assign * in the new decoded sign array in the current i location
			currentBit += 2; //jump to the next 2 bits
		}
		else if(first == '1' && second == '1') {
			dSignArray[i] = ':'; //assign : in the new decoded sign array in the current i location
			currentBit += 2; //jump to the next 2 bits
		}
		else if (first == '0' && second == '1') {
			dSignArray[i] = '.'; //assign . in the new decoded sign array in the current i location
			currentBit += 2; //jump to the next 2 bits		
		}
		else if (first == '0' && second == '0') {
			dSignArray[i] = ' '; //assign ' ' in the new decoded sign array in the current i location
			currentBit += 2; //jump to the next 2 bits	
		}
	}
	dSignArray[length] = '\0'; //assign \0 to the end of the decoded sign array to make it a big string
	return dSignArray;
}

void printSignArray(char* signArray, int length) {
	char* temp = createSignsDecode(signArray, length); //create the decoded sign array out of the compressed sign array
	printf("%s", temp); //print the sign array
}

int getCount(char* signArray, int length) {
	char* temp;
	temp = createSignsDecode(signArray, length); //create the decoded sign array out of the compressed sign array

	int colonCount = 0, asteriskCount = 0;
	for (int i = 0; i < strlen(temp); i++) {
		//counts how many asterisk and colon are in the array
		if (temp[i] == '*') { 
			asteriskCount++;
		}
		if (temp[i] == ':') {
			colonCount++;
		}
	}

	int difference = abs(colonCount - asteriskCount); //calculate the difference between the two integers
	return difference;
}

int evaluateDifference(char* SEQ1, char* SEQ2, int n) {
	char* temp;
	temp = createSigns(SEQ1, SEQ2, n); //create the compressed sign array out of the 2 sequences parameters
	return getCount(temp, strlen(SEQ2)); //calculate the difference between the asterisk and colon in the array and return it
}