#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>

void printArray(int** array, int m, int n) {
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
}
int findSquare(int** array, int m, int n, int size) {
	int numOfSquares = 0;
	if (size > 0 && size < fmin(n, m)) {
		int i, j, counter = 0, copyI, copyJ;
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				counter = 0;
				if (i + size <= m && j + size <= n) {
					for (copyI = i; copyI < i + size; copyI++) {
						for (copyJ = j; copyJ < j + size; copyJ++) {
							if (array[copyI][copyJ] == 0) {
								counter++;
							}
							else if (array[copyI][copyJ] == 1) {
								break;
							}
							else {
								break;
							}
						}
						if (array[copyI][copyJ] == 1) {
							break;
						}
						else if (counter == size * size) {
							break;
						}
					}
					
				}
				if (counter == size * size) {
					numOfSquares++;
				}
			}
		}
	}
	else {
		printf("Wrong size");
	}
	return numOfSquares;
}
int main() {
	int m, n;
	printf("Enter m & n\n");
	if (scanf("%d %d", &m, &n) == 2) {
		int** array = (int**)malloc(m * sizeof(int*));
		if (array != NULL) {
			int i, j, temp;
			for (i = 0; i < m; i++) {
				array[i] = (int*)malloc(n * sizeof(int));
				if (array[i] == NULL) {
					printf("Memory could not be allocated!!!");
				}
				for (j = 0; j < n; j++) {
					if (scanf("%d", &temp) == 1) {
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
			printArray(array, m, n);
			int size;
			if (scanf("%d", &size) == 1) {
				printf("Find: %d\n", findSquare(array, m, n, size));
			}
			else {
				printf("Wrong size!!!\n");
			}
			for (i = 0; i < m; i++) {
				free(array[i]);
			}
			free(array);
		}
		else {
			printf("Memory could not be allocated!!!");
		}
	}
	else {
		printf("Wrong input!!!");
	}
	
	return 0;
}
