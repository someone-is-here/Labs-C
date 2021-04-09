#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <malloc.h>

typedef struct node {
	int digit;
	struct node* next;
	struct node* prev;
}Node;
typedef struct list {
	struct node* head;
	struct node* tail;
	int size;
}List;
void PrintNum(List* list);
void Clear(List* list);
void AddDigit(List* list, int num);
void Mult(List* list, const int multNum);
void ResultInFile(List* list);
void tests(char fileName[10],int);
void fact(int num);
#endif
