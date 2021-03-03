#include "fib.h"
#include <assert.h>

int testNum() {
	assert(findRes(1) == 1);
}
int testNum1() {
	assert(findRes(45) == 6);
}
int testNum2() {
	assert(findRes(13) == 5);
}
int testNum3() {
	assert(findRes(234) == 3);
}
int testNum4() {
	assert(findRes(243) == 7);
}
int testNum5() {
	assert(findRes(243382) == -1);
}

#undef main
int main() {
	testNum();
	testNum2();
	testNum3();
	testNum4();
	testNum5();
	return 0;
}