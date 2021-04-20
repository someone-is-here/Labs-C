#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

void addNode(Node** root, int value) {
	if (*root == NULL) {
		*root = (Node*) malloc(sizeof(Node));
		assert(*root != NULL);
		(*root)->left = (*root)->right = NULL;
		(*root)->value = value;
	}
	else if (value < (*root)->value) {
		addNode(&((*root)->left), value);
	}
	else {
		assert(value != (*root)->value);
		addNode(&((*root)->right), value);
	}
}

Node* Minimum(Node* node) {
	if (node->left == NULL) {
		return node;
	}
	return Minimum(node->left);
}

Node* Erase(Node* root, int value) {
	if (root == NULL) {
		return root;
	}
	if (root->value < value) {
		root->right = Erase(root->right, value);
	}
	else if (root->value > value) {
		root->left = Erase(root->left, value);
	}
	else if (root->right != NULL && root->left != NULL) {
		root->value = Minimum(root->right)->value;
		root->right = Erase(root->right, root->value);
	}
	else {
		if (root->left != NULL) {
			root = root->left;
		}
		else if (root->right != NULL) {
			root = root->right;
		}
		else {
			root = NULL;
		}
	}
	return root;
}
void showTree(Node* root) {
	if (root == NULL) {
		return;
	}
	if (root->left) {
		showTree(root->left);
	}

	printf("%d ", root->value);

	if (root->right) {
		showTree(root->right);
	}
}

void InputTree(FILE* out, Node* root) {
	if (root == NULL) {
		return;
	}
	if (root->left) {
		InputTree(out, root->left);
	}

	fprintf(out, "%d ", root->value);

	if (root->right) {
		InputTree(out, root->right);
	}
}
void clearTree(Node* root) {
	if (root->left) {
		clearTree(root->left);
	}
	if (root->right) {
		clearTree(root->right);
	}
	free(root);
}

void addNodeQueue(NodeForQueue** node, int value, char symb, int valueNum) {
	if (*node == NULL) {
		*node = (NodeForQueue*)malloc(sizeof(NodeForQueue));
		assert(node != NULL);
		(*node)->next = NULL;
		(*node)->value = value;
		(*node)->symb = symb;
		(*node)->valueNum = valueNum;
	}
	else {
		addNodeQueue(&((*node)->next), value, symb, valueNum);
	}
}
void showQueue(NodeForQueue* node) {
	while (node != NULL) {
		printf("%d --  %c\n", node->value, node->symb);
		node = node->next;
	}
}
NodeForQueue* deleteQueue(NodeForQueue* node) {
	NodeForQueue* first = node->next;
	free(node);
	return first;
}
void clearQueue(NodeForQueue* node) {
	while (node != NULL) {
		NodeForQueue* newNode = node;
		if (node->next != NULL) {
			node = node->next;
			free(newNode);
		}
		else {
			free(newNode);
			break;
		}
	}
	node = NULL;
}