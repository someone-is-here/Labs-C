#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#define size 15
#include <time.h>
#include <stdio.h>
#include <assert.h>

void FullFillTrees(char fileName[10]) {
	Node** rootsArray = (Node**)malloc(sizeof(Node*) * size);
	int num, numValue;
	char symb;
	assert(rootsArray != NULL);
	FILE* file0 = fopen("treeInput.txt", "r");
	assert(file0 != NULL);
	for (int i = 0; i < size; i++) {
		Node* root = NULL;
		symb = ' ';
		while (symb != '\n') {
			if (fscanf(file0, "%d%c", &num, &symb) == 2) {
				addNode(&root, num);
			}
		}
		rootsArray[i] = root;
	}
	fclose(file0);

	NodeForQueue* queue = NULL;

	FILE* file = fopen(fileName, "r");
	assert(file != NULL);

	while (feof(file) == 0) {
		if (fscanf(file, "%d %c %d\n", &num, &symb, &numValue) == 3) {
			addNodeQueue(&queue, num, symb, numValue);
		}
	}
	fclose(file);

	while (queue != NULL) {
		if (queue->symb == 'A') {
			addNode(&rootsArray[queue->value], queue->valueNum);
		}
		else if (queue->symb == 'D') {
			Erase(rootsArray[queue->value], queue->valueNum);
		}
		queue = deleteQueue(queue);
	}

	FILE* out = fopen("output.txt", "w");
	assert(out != NULL);
	for (int i = 0; i < size; i++) {
		InputTree(out, rootsArray[i]);
		fprintf(out, "\n");
	}
	fclose(out);

	clearQueue(queue);
	for (int i = 0; i < size; i++) {
		clearTree(rootsArray[i]);
	}
	free(rootsArray);
}
int main() {
	FullFillTrees("input.txt");
	FullFillTrees("inpu1.txt");
	return 0;
}