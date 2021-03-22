#include "fib.h"
#include <assert.h>

void testNum(int num, int res) {
	assert(findRes(num) == res);
}
#undef main
int main() {
	testNum(1,1);
	testNum(45,7);
	testNum(13,5);
	testNum(234,3);
	testNum(243,7);
	testNum(243382,-1);

	return 0;
}