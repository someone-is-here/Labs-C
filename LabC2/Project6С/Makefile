all: createDir build test

createDir:
	mkdir -p target
build:
	gcc -o target/task1 task1.c -lm
test:
	gcc -o target/test task1.c test.c -Dmain=_main -lm
	./target/test
