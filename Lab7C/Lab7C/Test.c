#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <assert.h>
#include <string.h>

void test(char fileName[11]) {
	BaseWithStudents* base = (BaseWithStudents*)malloc(sizeof(BaseWithStudents));
	assert(base != NULL);
	base->head = base->tail = NULL;
	base->size = 0;
	readBaseFromFile(base);
	delStudent(base,"Tatiana", "Shurko");
	delStudent(base, "Dmitry", "Akinshev");
	Student* stud = (Student*)malloc(sizeof(Student));
	assert(stud != NULL);
	stud->anyPetitions = 0;
	stud->averageScore = 5.6;
	stud->socialAllowance = 1;
	char name[50] = "Zak";
	char surname[50] = "Michell";
	strcpy(stud->name, name);
	strcpy(stud->surname, surname);
	setScholarShip(stud);
	addStudent(base, stud);
	showAllBase(base);
	delStudent(base, "Zak", "Michell");
	BaseInFile(base, "output.txt");
	FILE* file0 = fopen(fileName, "r");
	FILE* file1= fopen("output.txt", "r");
	assert(file0 != NULL && file1 != NULL);
	char ch, ch1;
	while (feof(file0) == 0 && feof(file1) == 0){
		if (fscanf(file0, "%c", &ch) && fscanf(file1, "%c", &ch1)) {
			printf("%c%c",ch,ch1);
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
	changeAverageScore(base, "Tatiana", "Shurko", 8.7876);
	printStatement(base);
	BaseInFile(base, "output.txt");
	deleteBase(base);

	FILE* file0 = fopen(fileName, "r");
	FILE* file1 = fopen("output.txt", "r");
	assert(file0 != NULL && file1 != NULL);
	char ch, ch1;
	while (feof(file0) == 0 && feof(file1) == 0) {
		if (fscanf(file0, "%c", &ch) && fscanf(file1, "%c", &ch1)) {
			printf("%c%c",ch,ch1);
			//assert(ch == ch1);
		}
	}
	fclose(file0);
	fclose(file1);
}

#undef main
int main() {
	test("result.txt");
	//test1("result1.txt");
	return 0;
}
