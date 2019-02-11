#include "engine.h"

/*----------------Function for printing error messages and existing-------------------*/
void errorMessage(char* cmd) {
	char message[100];
	sprintf(message, "Usage: %s <no. of page frames (max. 100)> <a valid filename> <opt/lru/fifo>", cmd);
	write(2, message, strlen(message));
	exit(1);
}
/*------------------------------------------------------------------------------------*/

/*---------------Function to print the table------------------------------------------*/
void printTable(int current, int pageFrames, vector <int> table) {
	cout << current << ": [";
	for(int i=0; i<table.size(); i++) {
		if(table[i] < 10)
			cout << ' ';
		cout << table[i];
		if(i!=pageFrames-1)
			cout << '|';
	}
	for(int i=table.size(); i<pageFrames; i++) {
		cout << "  ";
		if(i!=pageFrames-1)
			cout << '|';
	}
	cout << ']';
}
/*------------------------------------------------------------------------------------*/

/*-------------Function to find if an element is present in a vector------------------*/
bool isPresent(vector <int> vec, int element, int * position) {
	bool present = false;
	for(int i=0; i<vec.size(); i++) {
		if(vec[i] == element) {
			present = true;
			*position = i;
		}
	}
	
	return present;
}
/*------------------------------------------------------------------------------------*/

/*---------------Function for the optimal algorithm-----------------------------------*/
void opt(int pageFrames, vector <int> vpns, bool verbose) {
	vector <int> table;
	int miss = 0;
	for(int i=0; i<vpns.size(); i++) {
		if(table.size() < pageFrames) {
			int index;
			bool present = isPresent(table, vpns[i], &index);
			if(!present) {
				table.push_back(vpns[i]);
				if(verbose) {
					printTable(vpns[i], pageFrames, table);
					cout << endl;
				}
			}
			else {
				if(verbose) {
					printTable(vpns[i], pageFrames, table);
					cout << endl;
				}
			}
		}
		else {
			int index;
			bool present = isPresent(table, vpns[i], &index);
			if(!present) {
				miss++;
				int ind[pageFrames], lastIndex = -1, eraseInd;
				bool present[5] = {false};
				for(int j=0; j<table.size(); j++) {
					present[j] = isPresent(vpns, table[j], &ind[j]);
					if(ind[j] < i) {
						lastIndex = -2;
						eraseInd = j;
						break;
					}
					else if(ind[j] > i) {
						if(lastIndex != -2 && ind[j] > lastIndex) {
							lastIndex = ind[j];
							eraseInd = j;
						}
					}
				}
				if(lastIndex != -1) {
					table.erase(table.begin() + eraseInd);
					table.insert(table.begin() + eraseInd, vpns[i]);
				}
				else {
					table.erase(table.begin());
					table.push_back(vpns[i]);
				}
				if(verbose) {
					printTable(vpns[i], pageFrames, table);
					cout << "  F" << endl;
				}
			}
			else {
				if(verbose) {
					printTable(vpns[i], pageFrames, table);
					cout << endl;
				}
                        }
		}
	}
	printf("Miss rate = %d/%d = %.2f", miss, vpns.size(), 100.0*miss/vpns.size());
	cout << (char) 37 << endl;
}
/*------------------------------------------------------------------------------------*/

/*------------------------Function for FIFO algorithm---------------------------------*/
void fifo(int pageFrames, vector <int> vpns, bool verbose) {
	int miss = 0, index = 0;
	vector <int> table;
	vector <int> ranks;
	for(int i=0; i<vpns.size(); i++) {
		if(table.size() < pageFrames) {
			if(!isPresent(table, vpns[i], &index)) {
				table.push_back(vpns[i]);
				if(verbose) {
					printTable(vpns[i], pageFrames, table);
					cout << endl;
				}
				for(int j=0; j<ranks.size(); j++) {
					ranks[j]++;
				}
				ranks.push_back(0);
			}
			else {
				if(verbose) {
					printTable(vpns[i], pageFrames, table);
					cout << endl;
				}
			}
		}
		else {
			if(!isPresent(table, vpns[i], &index)) {
				miss++;
				int eraseInd = -1;
				for(int j=0; j<table.size(); j++) {
					ranks[j]++;
					if(ranks[j] == pageFrames) {
						eraseInd = j;
						ranks[j] = 0;
					}
				}
				table.erase(table.begin() + eraseInd);
				table.insert(table.begin() + eraseInd, vpns[i]);
				if(verbose) {
					printTable(vpns[i], pageFrames, table);
					cout << "  F" << endl;
				}
			}
			else {
				if(verbose) {
					printTable(vpns[i], pageFrames, table);
					cout << endl;
				}
			}
		}
	}
	printf("Miss rate = %d/%d = %.2f", miss, vpns.size(), 100.0*miss/vpns.size());
	cout << (char) 37 << endl;
}
/*------------------------------------------------------------------------------------*/

/*-------------------------------LRU algorithm----------------------------------------*/
void lru(int pageFrames, vector <int> vpns, bool verbose) {
	int miss = 0, index = 0;
	vector <int> table;
	vector <int> last;
	
	for(int i=0; i<vpns.size(); i++) {
		if(table.size() < pageFrames) {
			if(!isPresent(table, vpns[i], &index)) {
				table.push_back(vpns[i]);
				last.push_back(i);
				if(verbose) {
					printTable(vpns[i], pageFrames, table);
					cout << endl;
				}
			}
			else {
				last[index] = i;
				if(verbose) {
					printTable(vpns[i], pageFrames, table);
					cout << endl;
				}
			}
		}
		else {
			if(!isPresent(table, vpns[i], &index)) {
				miss++;
				int minIndex = 100000000, eraseInd = -1;
				for(int j=0; j<last.size(); j++) {
					if(minIndex > last[j]) {
						minIndex = last[j];
						eraseInd = j;
					}
				}
				table[eraseInd] = vpns[i];
				last[eraseInd] = i;
				if(verbose) {
					printTable(vpns[i], pageFrames, table);
					cout << "  F" << endl;
				}
			}
			else {
				last[index] = i;
				if(verbose) {
					printTable(vpns[i], pageFrames, table);
					cout << endl;
				}
			}
		}
	}
	printf("Miss rate = %d/%d = %.2f", miss, vpns.size(), 100.0*miss/vpns.size());
	cout << (char) 37 << endl;
}
/*------------------------------------------------------------------------------------*/