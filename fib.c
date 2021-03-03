#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "fib.h"

int findNum(unsigned long num) {
	int kNum = 1;
	while (num > 9) {
		num /= 10;
		kNum++;
	}
	return kNum;
}

unsigned long int giveResNum(int* copyK, unsigned long int num) {
	if (*copyK == 0) {
		return num % 10;
	}
	++(*copyK);
	return giveResNum(copyK, num / 10);
}

unsigned long int findRes(int k) {
	int res = -1;
	if (k > 0 && k < 245) {
		int copyK = k;
		unsigned long int num1 = 1, num2 = 1, buffNum = 0;
		copyK -= 2;
		if (k == 1 || k == 2) {
			res = num1;
		}
		else {
			for (int i = 0; i < k; i++) {
				buffNum = num2;
				num2 += num1;
				num1 = buffNum;
				copyK -= findNum(num2);
				if (copyK <= 0) {
					res = giveResNum(&copyK, num2);
					break;
				}
			}
		}
	}
	else if (k >= 245) {
		printf("Number is too big");
	}
	else {
		printf("Wrong input!!!");
	}
	
	return res;
}

int main() {
	int k;
	scanf("%d", &k);
	printf("\n");
	if (k > 0) {
		printf("Result:  %d\n\n", findRes(k));
	}
	else if (k >= 245) {
		printf("Number is too big");
	}
	else {
		printf("Wrong input!!!");
	}

	return 0;
}
