#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <malloc.h>

typedef struct student {
	char name[50];
	char surname[50];
	double averageScore;
	//стипендия
	double scholarship;
	//only 1-yes; 0-no;
	//льготы
	int socialAllowance;
	//ходатайства
	int anyPetitions;
} Student;

//typedef struct baseWithStudents {
//	Student* students;
//	int numberOfStudents;
//	int capacity;
//} BaseWithStudents;

typedef struct node {
	Student person;
	struct node* next;
	struct node* prev;
}Node;
typedef struct baseWithStudents {
	struct node* head;
	struct node* tail;
	int size;
} BaseWithStudents;

void addStudent(BaseWithStudents*, Student*);
void delStudent(BaseWithStudents*, char[50], char[50]);
void showAllBase(BaseWithStudents*);
void deleteBase(BaseWithStudents*);
void readBaseFromFile(BaseWithStudents*);
void setScholarShip(Student*);
void changeAverageScore(BaseWithStudents*, char[50], char[50], double);
void changeSurname(BaseWithStudents*, char[50], char[50], char[50]);
void changeName(BaseWithStudents*, char[50], char[50], char[50]);
void setSocialAllowance(BaseWithStudents*, char[50], char[50]);
void addPetitions(BaseWithStudents*, char[50], char[50], int);
void printStatement(BaseWithStudents*);
void showMenu();
void baseInFile(BaseWithStudents*);
void test(char[11]);
void test1(char[12]);
#endif
