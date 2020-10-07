#include <stdio.h>
#include <string.h>
#include "func.h"
#define PRINT_SEQUENCES

void main(int argc, char *argv[]) { //pass the seq files to the command line
	char* SEQ1, * SEQ2, * signArray; //assign the arrays for sequences and signs
	int n = 0, difference = 0, difference1 = 0;

	SEQ1 = createSequence(argv[1]); //create the seq1 array
	SEQ2 = createSequence(argv[2]); //create the seq2 array
	n = 5; //the location which seq1 starts compared to seq2

	signArray = createSigns(SEQ1, SEQ2, n); //creates the sign array out of the sequences

	difference = evaluateDifference(SEQ1, SEQ2, n); //evaluate the difference and return it 

#ifdef PRINT_SEQUENCES //if the macro is defined than print 
		printf("%s \n", SEQ1); //print the seq1
		for (int space = 0; space < n; space++)
			printf(" ");

		printf("%s \n", SEQ2); //print the seq2
		for (int space = 0; space < n; space++)
			printf(" ");

		printSignArray(signArray, strlen(SEQ2)); //print the sin array
		printf("\n Difference : %d", difference); //print the difference
#endif

	//free all the arrays
	free(signArray);
	free(SEQ1);
	free(SEQ2);
}