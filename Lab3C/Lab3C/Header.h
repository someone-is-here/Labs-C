#ifndef HEADER
#define HEADER_H
void printArray(int** array, int m, int n);
int findSquare(int** array, int m, int n, int size);
int** readArrayFromFile(char fileName[9]);
void clearArray(int** array, int m);
int readM(char fileName[9]);
int readN(char fileName[9]);
void tests(char fileName[9], int size, int res);
#endif 
