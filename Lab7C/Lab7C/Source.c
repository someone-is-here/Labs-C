#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <assert.h>
#include <locale.h>
#include <string.h>

void addStudent(BaseWithStudents* base, Student* stud) {
	assert(stud != NULL);
	Node* node = (Node*) malloc (sizeof(Node));
	node->next = NULL;
	node->prev = NULL;
	node->person = *stud;
	if (base->head == NULL) {
		base->head = base->tail = node;
		base->size++;
	}
	else{
		base->tail->next = node;
		node->prev = base->tail;
		base->tail = node;
		base->size++;
	}
}
void delStudent(BaseWithStudents* base, char name[50], char surname[50]) {
	assert(base != NULL);
	Node* node = base->head;
	while (node != NULL) {
		if (strcmp(node->person.name, name) == 0 && strcmp(node->person.surname, surname) == 0) {
			if (node->next != NULL) {
				node->next->prev = node->prev;
			}
			else {
				base->tail = node->prev;
			}
			if (node->prev != NULL) {
				node->prev->next = node->next;
			}
			else {
				base->head = node->next;
			}
			base->size--;
			break;
		}
		node = node->next;
	}
}
void showAllBase(BaseWithStudents* base) {
	assert(base != NULL);
	Node* node = base->head;
	for (int i = 0; i < base->size; i++) {
		//printf("{%d}", i);
		printf("Name: %s %s\n", node->person.surname, node->person.name);
		printf("ScholarShip: %lf\n", node->person.scholarship);
		printf("Average score: %lf\n", node->person.averageScore);
		printf("Social allowance: %d\n", node->person.socialAllowance);
		printf("Number of petitions: %d\n", node->person.anyPetitions);
		node = node->next;
	}
}
void deleteBase(BaseWithStudents* base) {
	assert(base != NULL);
	Node* node = base->head;
	while (node->next != NULL){
		node = node->next;
		free(node->prev);
	}
	free(node);
	base = NULL;
}
void readBaseFromFile(BaseWithStudents* base) {
	assert(base != NULL);
    FILE* fin = fopen("base.txt","r"); 
	assert(fin != NULL);
	int num = 0;
	double allSum;
	while (fscanf(fin, "Total sum: %lf\n", &allSum) != 1) {
		Student* stud = (Student*)malloc(sizeof(Student));
		assert(stud != NULL);
		assert(fscanf(fin, "Name: %s %s\n", stud->surname, stud->name) == 2);
		assert(fscanf(fin, "ScholarShip: %lf\n", &stud->scholarship) == 1);
		assert(fscanf(fin, "Average score: %lf\n", &stud->averageScore) == 1);
		assert(fscanf(fin, "Social allowance: %d\n", &stud->socialAllowance) == 1);
		assert(fscanf(fin, "Number of petitions: %d\n", &stud->anyPetitions) == 1);
		setScholarShip(stud);
		addStudent(base, stud);
		num++;
	}

	fclose(fin);
}
void setScholarShip(Student* stud) {
	assert(stud != NULL);
	stud->scholarship = 0;
	if (stud->socialAllowance == 1) {
		stud->scholarship = 135.000;
	}
	if (stud->anyPetitions) {
		stud->scholarship = 181.000;
	}
	else {
		if (stud->averageScore >= 5 && stud->averageScore < 6) {
			stud->scholarship = 78.862;
		}
		else if (stud->averageScore >= 6 && stud->averageScore < 8) {
			stud->scholarship = 94.634;
		}
		else if (stud->averageScore >= 8 && stud->averageScore < 9) {
			stud->scholarship = 110.405;
		}
		else if (stud->averageScore >= 9 && stud->averageScore <= 10) {
			stud->scholarship = 126.179;
		}
	}
}

void changeAverageScore(BaseWithStudents* base, char name[50], char surname[50], double newAverageScore) {
	assert(base != NULL);
	assert(newAverageScore >= 0 && newAverageScore <= 10.0);
	Node* node = base->head;
	while (node != NULL) {
		if (strcmp(node->person.name, name) == 0 && strcmp(node->person.surname, surname) == 0) {
			node->person.averageScore = newAverageScore;
			setScholarShip(&node->person);
			break;
		}		
		node = node->next;
	}
}
void changeName(BaseWithStudents* base, char name[50], char surname[50], char newName[50]) {
	assert(base != NULL);
	Node* node = base->head;
	while (node != NULL) {
		if (strcmp(node->person.surname, surname) == 0 && strcmp(node->person.name, name) == 0) {
			int j = 0;
			while (newName[j] != '\0') {
				node->person.name[j] = newName[j];
				j++;
			}
			node->person.name[j] = '\0';
			break;
		}
		node = node->next;
	}
}
void changeSurname(BaseWithStudents* base, char name[50], char surname[50], char newSurname[50]) {
	assert(base != NULL);
	Node* node = base->head;
	while (node != NULL) {
		if (strcmp(node->person.name, name) == 0 && strcmp(node->person.surname,surname) == 0) {
			int j = 0;
			while (newSurname[j] != '\0') {
				node->person.surname[j] = newSurname[j];
				j++;
			}
			node->person.surname[j] = '\0';
			break;
		}
		node = node->next;
	}
}
void setSocialAllowance(BaseWithStudents* base, char name[50], char surname[50]) {
	assert(base != NULL);
	Node* node = base->head;
	while (node != NULL) {
		if (strcmp(node->person.name, name) == 0 && strcmp(node->person.surname, surname) == 0) {
			node->person.socialAllowance = 1;
			setScholarShip(&node->person);
			break;
		}
		node = node->next;
	}
}
void addPetitions(BaseWithStudents* base, char name[50], char surname[50], int num){
	assert(base != NULL);
	Node* node = base->head;
	while (node != NULL) {
		if (strcmp(node->person.name, name) == 0 && strcmp(node->person.surname, surname) == 0) {
			node->person.anyPetitions += num;
			setScholarShip(&node->person);
			break;
		}
		node = node->next;
	}
}
void printStatement(BaseWithStudents* base) {
	assert(base != NULL);
	double allSum = 0;
	Node* node = base->head;
	int i = 0;
	while (i++ < base->size) {
		//printf("{%d}", i);
		printf("Name: %s %s\n", node->person.surname, node->person.name);
		printf("ScholarShip: %lf\n", node->person.scholarship);
		printf("Average score: %lf\n", node->person.averageScore);
		printf("Social allowance: %d\n", node->person.socialAllowance);
		printf("Number of petitions: %d\n", node->person.anyPetitions);
		if(node->next != NULL)node = node->next;
		allSum += node->person.scholarship;
	}
	printf("Total sum: %lf\n", allSum);
}

void showMenu() {
	printf("Print 1 to add student to base\n");
	printf("Print 2 to delete student from base\n");
	printf("Print 3 to change student's name\n");
	printf("Print 4 to change student's surname\n");
	printf("Print 5 to change average score\n");
	printf("Print 6 to add social allowance\n");
	printf("Print 7 to add petitions\n");
	printf("Print 8 to dump the database\n");
	printf("Print 9 show all database\n");
	printf("Print other keys if you want to eixt\n");
}
void baseInFile(BaseWithStudents* base) {
	assert(base != NULL);
	double allSum = 0;
	Node* node = base->head;
	int i = 0;
	FILE* file = fopen("base.txt","w");
	assert(file != NULL);
	while (node != NULL) {
		fprintf(file, "Name: %s %s\n", node->person.surname, node->person.name);
		fprintf(file, "ScholarShip: %lf\n", node->person.scholarship);
		fprintf(file, "Average score: %lf\n", node->person.averageScore);
		fprintf(file, "Social allowance: %d\n", node->person.socialAllowance);
		fprintf(file, "Number of petitions: %d\n", node->person.anyPetitions);
		allSum += node->person.scholarship;
		node = node->next;
	}
	fprintf(file, "Total sum: %lf", allSum);
	fclose(file);
}

void test(char fileName[11]) {
	BaseWithStudents* base = (BaseWithStudents*)malloc(sizeof(BaseWithStudents));
	assert(base != NULL);
	base->head = base->tail = NULL;
	base->size = 0;
	readBaseFromFile(base);
	delStudent(base, "Tatiana", "Shurko");
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
	char surname[50] = "Shurko";
	strcpy(stud->name, name);
	strcpy(stud->surname, surname);
	addStudent(base, stud);
	setSocialAllowance(base, "Tatiana", "Shurko");
	addPetitions(base, "Tatiana", "Shurko", 5);
	changeAverageScore(base, "Tatiana", "Shurko", 8.7876);
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

int main() {
	test("result.txt");
	test1("result1.txt");

	return 0;
}