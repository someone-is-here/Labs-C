#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

void AddDigit(List* list, int num) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->prev = NULL;
	newNode->next = NULL;
	newNode->digit = num;
	if (list->head == NULL) {
		list->head = list->tail = newNode;
		list->size++;
	}
	else {
		list->head->prev = newNode;
		newNode->next = list->head;
		list->head = newNode;
		list->size++;
	}
}
void PrintNum(List* list) {
	Node* newNode = list->head;
	while (newNode != NULL) {
		printf("%d", newNode->digit);
		newNode = newNode->next;
	}
	printf("\n");
	free(newNode);
}
void Clear(List* list) {
	Node* newNode = list->head;
	while (newNode->next != NULL) {
		newNode = newNode->next;
		free(newNode->prev);
	}
	list->size = 0;
	free(newNode);
	free(list);
}
void Mult(List* list, const int multNum) {
	Node* newNode = list->tail;
	int number = 0;
	int tempNum;
	while (newNode != NULL) {
		newNode->digit *= multNum;
		tempNum = newNode->digit;
		newNode->digit = (tempNum + number) % 10;
		number = (tempNum + number) / 10;
		newNode = newNode->prev;
	}
	while (number > 9) {
		AddDigit(list, number % 10);
		number /= 10;
	}
	if (number != 0) {
		AddDigit(list, number);
	}
}
void ResultInFile(List* list) {
	FILE* file = fopen("output.txt", "w");
	Node* newNode = list->head;
	for (int i = 0; i < list->size; i++) {
		fprintf(file, "%d", newNode->digit);
		newNode = newNode->next;
	}
	fclose(file);
}

