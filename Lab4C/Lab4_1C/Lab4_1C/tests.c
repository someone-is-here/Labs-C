#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Header.h"
#include <assert.h>
#include <locale.h>

void test(char fileName[9], char fileInput[9]) {
	printf("function\n");
	readFile(fileInput, 0);
	char ch, ch1;
	FILE* file = fopen("output.txt", "r");
	FILE* file1 = fopen(fileName, "r");
	if (file != NULL && file1 != NULL) {
		while (feof(file) == 0 && feof(file1) == 0) {
			if (fscanf(file, "%c", &ch) && fscanf(file1, "%c", &ch1)) {
				printf("%c  %c\n",ch,ch1);
				assert(ch == ch1);
			}
		}
		fclose(file);
		fclose(file1);
	}
	else {
		printf("file can't be opened\n");
	}
}

#undef main

int main() {
	setlocale(LC_ALL, "Russian");
	test("test1.txt", "input.txt");
	test("test2.txt", "input2.txt");
	test("test3.txt", "input3.txt");
	return 0;
}
