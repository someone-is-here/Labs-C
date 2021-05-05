#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <assert.h>

void test(char fileName[11]) {
	BaseWithStudents* base = (BaseWithStudents*)malloc(sizeof(BaseWithStudents));
	assert(base != NULL);
	base->head = base->tail = NULL;
	base->size = 0;
	readBaseFromFile(base);
	delStudent(base,"Tatiana", "Shurko");
	BaseInFile(base, "resul.txt");
	FILE* file0 = fopen(fileName, "r");
	FILE* file1= fopen("resul.txt", "r");
	assert(file0 != NULL && file1 != NULL);
	char ch, ch1;
	while (feof(file0) == 0 && feof(file1) == 0){
		if (fscanf(file0, "%c", &ch) && fscanf(file1, "%c", &ch1)) {
			printf("%c %c",ch,ch1);
			//assert(ch == ch1);
		}
	}
	deleteBase(base);
	fclose(file0);
	fclose(file1);
}
void test1(char fileName[12]) {
	BaseWithStudents* base = (BaseWithStudents*)malloc(sizeof(BaseWithStudents));
	assert(base != NULL);
	base->head = base->tail = NULL;
	base->size = 0;
	readBaseFromFile(base);
	setSocialAllowance(base, "Tatiana", "Shurko");
	addPetitions(base, "Tatiana", "Shurko", 5);
	changeAverageScore(base, "Tatiana", "Shurko", 9.9876);

	BaseInFile(base, "resul.txt");
	deleteBase(base);

	FILE* file0 = fopen(fileName, "r");
	FILE* file1 = fopen("resul.txt", "r");
	assert(file0 != NULL && file1 != NULL);
	char ch, ch1;
	while (feof(file0) == 0 && feof(file1) == 0) {
		if (fscanf(file0, "%c", &ch) && fscanf(file1, "%c", &ch1)) {
			printf("%c %c",ch,ch1);
			//assert(ch == ch1);
		}
	}
	fclose(file0);
	fclose(file1);
}

#undef main
int main() {
	test("result.txt");
	test1("Result1.txt");
	return 0;
}
