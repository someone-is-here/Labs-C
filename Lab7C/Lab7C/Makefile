all: createDir build test

createDir:
	mkdir -p target
build:
	gcc -o target/Source Source.c -lm
test:
	gcc -o target/test Source.c Test.c -Dmain=_main -lm
	./target/test