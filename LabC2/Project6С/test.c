#include "Header.h"
#include <assert.h>
void test1(int num1, int num2, int num3, float num4, int res) {
	assert(chooseFaculty(num1, num2, num3, num4) == res);
}

void testFact(double num,double res) {
	assert(findFact(num) == res);
}

void test2(double x, int n, double dif) {
	assert(findDif(x,n) == dif);
}

void test3(double x, double dif, int n) {
	assert(findN(x, dif) == n);
}

#undef main

int main() {
	testFact(5, 120.0);
	testFact(4, 24.0);
	testFact(6, 720.0);
	test1(88, 81, 87, 10.0, 356);
	test1(77, 77, 77, 7.7, 308);
	test3(1.57, 0.000035, 5);
	test3(1.57, 0.001, 4);
	test3(3, 0.03, 5);
	test3(2.75, 0.000000000032447877718055906370864249765872955322265625,10);
	return 0;
}
