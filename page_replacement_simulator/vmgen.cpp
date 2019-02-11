#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>
using namespace std;

/*---Error Message-------------------------------------------*/
void errorMessage(char* cmd) {
	char message[100];
	sprintf(message, 
		"Usage: %s <range of page references> <length of the sequence> <filename>", cmd);
	message[strlen(message)] = (char) 0;
	write(2, message, strlen(message));
	exit(1);
}
/*-----------------------------------------------------------*/

int main(int argc, char* argv[]) {
/*------Checking for required arguments----------------------*/
	if(argc != 4) {
		errorMessage(argv[0]);
	}
	else if(atoi(argv[1]) > 100 || atoi(argv[1]) < 1) {
		errorMessage(argv[0]);
	}
	else if(atoi(argv[2]) > 100 || atoi(argv[2]) < 1) {
		errorMessage(argv[0]);
	}
/*-----------------------------------------------------------*/	

/*------Opening file for writing-----------------------------*/
	FILE *output;
	output = fopen(argv[3], "w");
	if(!output) {
		write(2, "Error creating/rewriting file", 28);
	}
/*-----------------------------------------------------------*/

/*------Writing to file--------------------------------------*/
	srand(time(NULL));
	int randomPageNumber, last = 0;
	for(int i=0; i<atoi(argv[2]); i++) {
		randomPageNumber = rand()%atoi(argv[1]) + 1;
		if(randomPageNumber == last) {
			i--;
			continue;
		}
		fprintf(output, "%d ", randomPageNumber);
		last = randomPageNumber;
	}
/*-----------------------------------------------------------*/

/*------Closing file-----------------------------------------*/
	fclose(output);
/*-----------------------------------------------------------*/
	return 0;
}
