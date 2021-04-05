#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <malloc.h>

void checkString(const char str[100], int size, int num) {
	int i = 0;
	int j = size;
	char* newStr = (char*)malloc(size * sizeof(char));
	int count = 0;
	int index = 0;
	FILE* file = fopen("result.txt", "w");
	if (file != NULL) {
		while (str[i] != '(' && i < j) {
			if (str[i] == ')') {
				fprintf(file, "Wrong input\n");
				free(newStr);
				return;
			}
			i++;
		}
		while (str[--j] != ')' && j > 0) {
			if (str[j] == '(') {
				fprintf(file, "Wrong input\n");
				free(newStr);
				return;
			}
		}

		for (i = 0; i < size; i++) {
			if (str[i] == '(') {
				count++;
				newStr[index++] = str[i];
			}
			else if (str[i] == ')') {
				count--;
				newStr[index++] = str[i];
			}
			else {
				if (!count) {
					newStr[index++] = str[i];
				}
			}
		}

		if (count) {
			fprintf(file, "Wrong input\n");
			free(newStr);
			return;
		}

		if (!count) {
			fprintf(file, "%d\n", index);
			for (i = 0; i < index; i++) {
				if (num) {
					printf("%c", newStr[i]);
				}
				putc(newStr[i], file);
			}
		}
		fclose(file);
	}
	else {
		printf("Can't open file!\n");
	}
	free(newStr);
}
int main() {
	int size = 100;
	int index = 0;
	char* str = (char*)malloc(size * sizeof(char));
	char ch;
	while (scanf("%c", &ch) && index < 100) {
		if (ch != '\n') {
			str[index] = ch;
			index++;
		}
		else {
			break;
		}
	}
	checkString(str, index, 1);
	free(str);
	return 0;
}