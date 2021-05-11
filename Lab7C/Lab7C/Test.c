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
	baseInFile(base);
	deleteBase(base);

	FILE* file0 = fopen(fileName, "r");
	FILE* file1 = fopen("base.txt", "r");
	assert(file0 != NULL && file1 != NULL);
	char str1[50];
	char str2[50];
	while (feof(file0) == 0 && feof(file1) == 0) {
		if (fscanf(file0, "%s", str1) && fscanf(file1, "%s", str2)) {
			assert(strcmp(str1, str2) == 0);
		}
	}
	fclose(file0);
	fclose(file1);
}
void test1(char fileName[12]) {
	BaseWithStudents* base = (BaseWithStudents*)malloc(sizeof(BaseWithStudents));
	assert(base != NULL);
	base->head = base->tail = NULL;
	base->size = 0;
	readBaseFromFile(base);
	Student* stud = (Student*)malloc(sizeof(Student));
	assert(stud != NULL);
	stud->anyPetitions = 2;
	stud->averageScore = 9.6;
	stud->socialAllowance = 1;
	char name[50] = "Tatiana";
	char surname[50] = "Shurk";
	strcpy(stud->name, name);
	strcpy(stud->surname, surname);
	addStudent(base, stud);
	setSocialAllowance(base, "Tatiana", "Shurk");
	addPetitions(base, "Tatiana", "Shurk", 5);
	changeAverageScore(base, "Tatiana", "Shurk", 8.7876);
	changeName(base, "Tatiana", "Shurk", "Tanusha");
	changeSurname(base, "Tanusha", "Shurk", "Shurko");
	printStatement(base);
	baseInFile(base);
	showMenu();
	deleteBase(base);

	FILE* file0 = fopen(fileName, "r");
	FILE* file1 = fopen("base.txt", "r");
	assert(file0 != NULL && file1 != NULL);
	char str1[50];
	char str2[50];
	while (feof(file0) == 0 && feof(file1) == 0) {
		if (fscanf(file0, "%s", str1) && fscanf(file1, "%s", str2)) {
			assert(strcmp(str1, str2) == 0);
		}
	}
	fclose(file0);
	fclose(file1);
}

#undef main
int main() {
	test("result.txt");
	test1("result1.txt");
	return 0;
}
