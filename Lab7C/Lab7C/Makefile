all: createDir build test

createDir:
	mkdir -p target
build:
	gcc --coverage -o test Test.c Source.c -Dmain=_main -lm
	gcc -o target/Source Source.c -lm
	gcov Source.c
test:
	gcc -o target/test Source.c Test.c -Dmain=_main -lm
	./target/test
