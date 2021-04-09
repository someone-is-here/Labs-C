#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

void fact(int num) {
	List* list = (List*)malloc(sizeof(List));
	list->head = list->tail = NULL;
	list->size = 0;
	AddDigit(list, 1);
	if (num > 0) {
		int i;
		for (i = 1; i <= num; i++) {
			Mult(list, i);
		}
	}
	PrintNum(list);
	ResultInFile(list);
	Clear(list);
}

int main() {
	fact(100);
	return 0;
}