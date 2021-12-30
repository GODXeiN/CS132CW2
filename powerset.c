#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//2^input Method

unsigned long int twoPow(unsigned long int input) {
	unsigned long int i;
	unsigned long int output = 1;

	for (i = 0; i < input; i++) {
		output *= 2;
	}
	return output;
}

int main() {
	
	// Declaration of data for input

	unsigned long int arraySize;
	unsigned long int i;

	printf("Please enter the cardinality of your set S: \n");
	scanf("%llu", &arraySize);

	// If it empty set, the output is immediate

	if (arraySize == 0) {
		printf("The power set of your entered set S is : \n");
		printf("{{}} \n");
		return 0;	
	}

	// Declaration of data to process the input
	
	char *S[arraySize];
	char *powerSetS[twoPow(arraySize)];
	char *powerSetSStar[twoPow(arraySize-1) - 1];
	size_t malloc_size = 10000;

	// Input of elements of the set S by the user

	for (i = 0; i < arraySize; i++) {
    		S[i] = malloc(malloc_size * sizeof(char)); /* allocates 1000 bytes */
    		printf("Enter element: ");
    		scanf("%999s", S[i]); /* set as 999 to avoid overflow */
	}

	// Allocation of memory to pointer array for strings

	for (i = 0; i < twoPow(arraySize-1); i++) {
		powerSetSStar[i] = malloc(malloc_size * sizeof(char)); /* allocates 1000 bytes */
	}

	for (i = 0; i < twoPow(arraySize); i++) {
		powerSetS[i] = malloc(malloc_size * sizeof(char)); /* allocates 1000 bytes */
	}

	// The previously explained mathematical algorithm in action
	
	for (i = 0; i < arraySize; i++) {
		
		// Declaration of variables for loops

		unsigned long int k; 
		unsigned long int n;

		if (i == 0) {
			powerSetS[i] = S[i]; /* Adding a singleton to initiate the algorithm */
		}	
		else {
			for (k = 0; k < twoPow(i)-1; k++) {
				strcpy(powerSetSStar[k], powerSetS[k]); /* copy each element */
				strcat(powerSetSStar[k], ", "); /* comma element separator for each subset */
				strcat(powerSetSStar[k], S[i]); /* add new element to each previously defined element */
				strcpy(powerSetS[twoPow(i) - 1 + k], powerSetSStar[k]); /* set the new elements back to the power set */
				n = k;
			}
			strcpy(powerSetS[twoPow(i) + n], S[i]); /* add the singleton element */
		}

	}

	powerSetS[twoPow(arraySize)-1] = ""; /* defining the empty set */

	// Printing power set

	printf("The subsets for your set S are (each separated by a new line): \n");
	for (i = 0; i < twoPow(arraySize); i++) {
		printf("{%s} \n", powerSetS[i]);
	}
	return 0;
}

