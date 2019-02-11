#include "engine.h"

int main(int argc, char* argv[]) {
	
/*------------------------Error messages for inaccurate arguments---------------------*/
	if(argc!=4) {
		errorMessage(argv[0]);
	}
	else if(atoi(argv[1]) < 1 || atoi(argv[1]) > 100) {
		errorMessage(argv[0]);
	}
	else if(strcmp(argv[3], "lru") && strcmp(argv[3], "opt") && strcmp(argv[3], "fifo")) {
		errorMessage(argv[0]);
	}
/*------------------------------------------------------------------------------------*/

/*---------------------------------File reading---------------------------------------*/
	FILE *input;
	input = fopen(argv[2], "r");
	/*-------------------------Error--------------------------*/
	if(!input) {
		write(2, "Invalid filename or corrupt file\n", 34);
		exit(2);
	}
	/*-------------------------------------------------------*/

	/*-----------------Algorithm Parameters------------------*/
	vector <int> vpns;
	int vpn;
	while(fscanf(input, "%d", &vpn) != EOF) {
		vpns.push_back(vpn);
	}

	fclose(input);
	int pageFrames = atoi(argv[1]);
	/*---------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/	

/*-------------------------------Algorithm Function Call------------------------------*/
	if(strcmp(argv[3], "opt") == 0)
		opt(pageFrames, vpns, true);
	else if(strcmp(argv[3], "lru") == 0)
		lru(pageFrames, vpns, true);
	else
		fifo(pageFrames, vpns, true);
/*------------------------------------------------------------------------------------*/
	return 0;
}
