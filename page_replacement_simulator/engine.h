#ifndef _engine
#define _engine
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
using namespace std;

void errorMessage(char *);

void printTable(int, int, std::vector <int>); 

bool isPresent(vector <int>, int, int *);

void opt(int, std::vector<int>, bool);

void lru(int, std::vector<int>, bool);

void fifo(int, std::vector<int>, bool);

#endif