#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
int checkWord(unsigned char str[100],int size) {
	int counter = 0;
	for (int i = 0; i < size; i++) {
		switch (str[i]) {
		case -64:
		case -62:
		case -47:
		case -59:
		case -46:
		case -50:
		case -48:
		case -43:
		case -52:
		case -51:
		case -54:
			counter++;
			break;
		}
	}
	return counter;
}
void readFile(char fileName[9], int num) {
	char ch;
	char * word = (char *)malloc(sizeof(char ) * 100);
	int index = 0;
	FILE* file = fopen(fileName, "r");
	FILE* file1 = fopen("output.txt", "w");
	if (file != NULL && file1 != NULL) {
		while (fscanf(file, "%c", &ch) && feof(file) == 0) {
			if (ch != ' ' && ch != '\n') {
				word[index] = ch;
				index++;
			}
			else {
				if (checkWord(word, index) == index && index) {
					for (int i = 0; i < index; i++) {
						if (num) {
							printf("%c", word[i]);
						}
						fprintf(file1, "%c", word[i]);
					}
					if (num) {
						printf("\n");
					}
					fprintf(file1, "\n");
				}
				index = 0;
			}
		}
		if (index) {
			if (checkWord(word, index) == index) {
				for (int i = 0; i < index; i++) {
					if (num) {
						printf("%c", word[i]);
					}
					fprintf(file1, "%c", word[i]);
				}
				if (num) {
					printf("\n");
				}
				fprintf(file1, "\n");
			}
			index = 0;
		}
		fclose(file);
		fclose(file1);
		free(word);
	}
	else {
		printf("Can't open file!\n");
	}
}
int main() {
	setlocale(LC_ALL, "Russian");
	readFile("input.txt", 1);
	return 0;
}
