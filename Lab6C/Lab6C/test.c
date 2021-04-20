#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <assert.h>

void tests(char input[10],char fileName[10]) {
	FullFillTrees(input);
	FILE* file = fopen("output.txt", "r");
	FILE* file1 = fopen(fileName, "r");
	int num, num1;

	assert(file != NULL);
	assert(file1 != NULL);

	while (feof(file) == 0 && feof(file1) == 0) {
		if (fscanf(file, "%d", &num) && fscanf(file1, "%d", &num1)) {
			assert(num == num1);
		}
	}
	fclose(file1);
	fclose(file);
}

#undef main

int main() {
	tests("input.txt", "test1.txt");
	tests("inpu1.txt", "test2.txt");
	return 0;
}
