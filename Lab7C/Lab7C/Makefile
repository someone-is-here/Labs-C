all: clean buildMain buildTest runTest

buildMain:
	mkdir -p target/test
	gcc -o target/test/Source Test.c Source.c -Dmain=_main -lm

buildTest:
	gcc -ftest-coverage -fprofile-arcs -O0 -o test Source.c Test.c -Dmain=_main -lm

runTest:
	./test
	gcov -abcfu Test.c

clean:
	rm -rf target
