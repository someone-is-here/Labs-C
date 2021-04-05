#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <assert.h>
#include <stdio.h>

void test(const char stringForChecking[100],int stringForCheckingLength, const char fileName[10], const char fileNameTest[9]) {
	checkString(stringForChecking, stringForCheckingLength, 0);
	FILE* myfile = fopen(fileName, "r");
	FILE* mytest = fopen(fileNameTest, "r");
	int index;
	if (myfile != NULL && mytest != NULL) {
		if (fscanf(myfile, "%d\n", &index) == 1) {
			while (index) {
				assert(getc(myfile) == getc(mytest));
				index--;
			}
		}
		fclose(myfile);
		fclose(mytest);
	}
	else {
		printf("Can't open file!\n");
	}
}

#undef main

int main() {
	test("(my life is)  something(you can't ive with) foolish", 51, "result.txt", "test1.txt");
	test("))", 2, "result.txt", "test2.txt");
	test("(bjkfd)(Nbfd", 12, "result.txt", "test3.txt");
	test("((my life is)  something)here? smth (you can't ive with) foolish:/", 66, "result.txt", "test4.txt");
	test("hello world(smth) ((loop (in air)(get)))", 40, "result.txt", "test5.txt");
	return 0;
}