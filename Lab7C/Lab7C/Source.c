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
	else {
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
	printf("\n\nChange name\n\n");
	assert(base != NULL);
	Node* node = base->head;
	while (node != NULL) {
		if (strcmp(node->person.surname, surname) == 0 && strcmp(node->person.name, name) == 0) {
			int j = 0;
			printf("\n\nFound\n\n");
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
	printf("\n\nChange surname\n\n");
	assert(base != NULL);
	Node* node = base->head;
	while (node != NULL) {
		if (strcmp(node->person.name, name) == 0 && strcmp(node->person.surname,surname) == 0) {
			int j = 0;
			printf("\n\nFound\n\n");
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

int main() {
	BaseWithStudents* base = (BaseWithStudents*)malloc(sizeof(BaseWithStudents));
	base->head = base->tail = NULL;
	base->size = 0;
	
	readBaseFromFile(base);
	Student* alice = (Student*)malloc(sizeof(Student));
	assert(alice != NULL);
	while (1) {
		showMenu();
		char name[50];
		char surname[50];
		switch (getchar()) {
		case '1':
			printf("Enter name and surname\n");
			assert(scanf("%s %s", alice->name, alice->surname) == 2);
			printf("Enter average score\n");
			assert(scanf("%lf", &alice->averageScore) == 1);
			printf("Enter social allowance\n");
			assert(scanf("%d", &alice->socialAllowance) == 1);
			printf("Enter petition's number\n");
			assert(scanf("%d", &alice->anyPetitions) == 1);
			setScholarShip(alice);
			addStudent(base, alice);
			break;
		case '2':
			printf("Enter surname and name\n");
			assert(scanf("%s %s", surname, name) == 2);
			delStudent(base, name, surname);
			break;
		case '3':
			printf("Enter surname and name\n");
			assert(scanf("%s %s", surname, name) == 2);
			printf("Enter new name\n");
			assert(scanf("%s", alice->name) == 1);
			changeName(base, name, surname, alice->name);
			break;
		case '4':
			printf("Enter surname and name\n");
			assert(scanf("%s %s", surname, name) == 2);
			printf("Enter new surname\n");
			assert(scanf("%s", alice->surname) == 1);
			changeSurname(base, name, surname, alice->surname);
			break;
		case '5':
			printf("Enter surname and name\n");
			assert(scanf("%s %s", surname, name) == 2);
			printf("Enter new average score\n");
			assert(scanf("%lf", &alice->averageScore) == 1);
			changeAverageScore(base, name, surname, alice->averageScore);
			break;
		case '6':
			printf("Enter surname and name\n");
			assert(scanf("%s %s", surname, name) == 2);
			printf("Enter social allowance\n");
			assert(scanf("%d", &alice->socialAllowance) == 1);
			setSocialAllowance(base, name, surname);
			break;
		case '7':
			printf("Enter surname and name\n");
			assert(scanf("%s %s", surname, name) == 2);
			printf("Enter petition's number\n");
			assert(scanf("%d", &alice->anyPetitions) == 1);
			addPetitions(base, name, surname, alice->anyPetitions);
			break;
		case '8':
			printStatement(base);
			break;
		case '9':
			showAllBase(base);
			break;
		default:
			baseInFile(base);
			exit(0);
			deleteBase(base);
		}
		getchar();
		free(alice);
	}

	deleteBase(base);

	return 0;
}
