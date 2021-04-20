#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <malloc.h>

typedef struct node {
	int value;
	struct node* right;
	struct node* left;
} Node;

void addNode(Node** root, int value);
Node* Erase(Node* root, int value);
Node* Minimum(Node* node);
void showTree(Node* root);
void InputTree(FILE* out, Node* root);
void clearTree(Node* root);

typedef struct nodeForQueue {
	int value;
	char symb;
	int valueNum;
	struct nodeForQueue* next;
} NodeForQueue;


void addNodeQueue(NodeForQueue** node, int value, char symb, int valueNum);
NodeForQueue* deleteQueue(NodeForQueue* node);
void showQueue(NodeForQueue* node);
void clearQueue(NodeForQueue* node);

void tests(char input[10], char fileName[10]);
void FullFillTrees(char fileName[10]);

#endif
