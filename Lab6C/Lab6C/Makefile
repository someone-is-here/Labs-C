all: createDir build test

createDir:
	mkdir -p target
build:
	gcc -o target/Source Source.c BinaryTree.c -lm
test:
	gcc -o target/test Source.c test.c BinaryTree.c -Dmain=_main -lm
	./target/test