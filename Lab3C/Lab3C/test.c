#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int readM(char fileName[9]) {
	FILE* myfile;
	myfile = fopen(fileName, "r");
	int m = 0;
	if (myfile == NULL) {
		printf("can't open file");
	}
	else {
		if (fscanf(myfile, "%d", &m) == 1) 
		fclose(myfile);
	}
	return m;
}
int readN(char fileName[9]) {
	FILE* myfile;
	myfile = fopen(fileName, "r");
	int m = 0, n = 0;
	if (myfile == NULL) {
		printf("can't open file");
	}
	else {
		if (fscanf(myfile, "%d %d", &m, &n) == 2)
		fclose(myfile);
	}
	return n;
}
int** readArrayFromFile(char fileName[9]) {
	FILE* myfile;
	myfile = fopen(fileName, "r");
	int m, n;
	if (fscanf(myfile,"%d %d", &m, &n) == 2) {
		int** array = (int**)malloc(m * sizeof(int*));
		if (array != NULL) {
			int i, j, temp;
			for (i = 0; i < m; i++) {
				array[i] = (int*)malloc(n * sizeof(int));
				if (array[i] == NULL) {
					printf("Memory could not be allocated!!!");
				}
				for (j = 0; j < n; j++) {
					if (fscanf(myfile,"%d", &temp) == 1) {
						if (temp != 0 && temp != 1) {
							printf("wrong input");
							exit(0);
						}
						array[i][j] = temp;
					}
					else {
						printf("wrong input");
						exit(0);
					}
				}
			}
			fclose(myfile);
			return array;
		}
		else {
			printf("Memory could not be allocated!!!");
		}
	}
	else {
		printf("Wrong input!!!");
	}
	return NULL;
}
void clearArray(int** array, int m) {
	int i;
	for (i = 0; i < m; i++) {
		free(array[i]);
	}
	free(array);
}
void tests(char fileName[9], int size, int res) {
	assert(findSquare(readArrayFromFile(fileName),readM(fileName),readN(fileName),size) == res);
}

#undef main

int main() {
	int m = readM("test1.txt");
	int** array = readArrayFromFile("test1.txt");
	clearArray(array, m);
	tests("test1.txt", 3, 1);
	tests("test1.txt", 2, 5);
	tests("test2.txt", 2, 2);
	tests("test2.txt", 1, 10);
	tests("test3.txt", 3, 2);
	tests("test3.txt", 2, 8);
	return 0;
}
