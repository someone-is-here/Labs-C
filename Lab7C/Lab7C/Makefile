all: createDir build test

createDir:
	mkdir -p target
build:
	gcc --coverage -o test Test.c Source.c -Dmain=_main -lm
	gcc -o target/Source Source.c -lm
test:
	gcc -o target/test Source.c Test.c -Dmain=_main -lm
	gcov Source.c
	./target/test
