all: createDir build test

createDir:
	mkdir -p target
build:
	gcc -o target/task1 task1.c
test:
	gcc -o target/test task1.c test.c -Dmain=_main
	./target/test