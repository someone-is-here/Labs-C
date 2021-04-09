#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include "Header.h"

void tests(char fileName[10], int numb) {
	fact(numb);
	FILE* file = fopen("output.txt", "r");
	FILE* file1 = fopen(fileName, "r");
	int num, num1;
	if (file != NULL && file1 != NULL) {
		while (feof(file) == 0 && feof(file1) == 0) {
			if (fscanf(file, "%d", &num) && fscanf(file1, "%d", &num1)) {
				assert(num == num1);
			}
		}
		fclose(file1);
		fclose(file);
	}
	else {
		printf("Wrong file\n");
	}
}

#undef main
int main() {
	tests("test1.txt", 100);
	tests("test2.txt", 500);
	tests("test3.txt", 250);
	return 0;
}