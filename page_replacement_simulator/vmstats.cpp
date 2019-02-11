#include "engine.h"

int main(int argc, char* argv[]) {
/*------Checking command line arguments-------------*/
	if(argc != 5) {
		errorMessage(argv[0]);
	}
	if(atoi(argv[1])<2 || atoi(argv[1])>100) {
		errorMessage(argv[0]);
	}
	if(atoi(argv[2])<2 || atoi(argv[2])>100 || atoi(argv[2]) < atoi(argv[1])) {
		errorMessage(argv[0]);
	}
/*--------------------------------------------------*/
	
/*------Opening file for reading--------------------*/
	FILE * input;
	input = fopen(argv[4], "r");
	if(!input) {
		write(2, "Invalid filename or corrupt file", 33);
		exit(1);  
	}
/*--------------------------------------------------*/

/*------Reading from file---------------------------*/
	vector <int> vpns;
	int vpn;
	while(fscanf(input, "%d", &vpn)!=EOF) {
		vpns.push_back(vpn);
	}
/*--------------------------------------------------*/

/*------Running Algorithms--------------------------*/
	for(int i = atoi(argv[1]); i <= atoi(argv[2]); i+=atoi(argv[3])) {
		cout << "opt " << i << " frames: ";
		opt(i, vpns, false);
	}
	for(int i = atoi(argv[1]); i <= atoi(argv[2]); i+=atoi(argv[3])) {
		cout << "lru " << i << " frames: ";
		lru(i, vpns, false);
	}
	for(int i = atoi(argv[1]); i <= atoi(argv[2]); i+=atoi(argv[3])) {
		cout << "fifo " << i << " frames: ";
		fifo(i, vpns, false);
	}
/*--------------------------------------------------*/

/*------Closing file--------------------------------*/
	fclose(input);
/*--------------------------------------------------*/
	return 0;
}
