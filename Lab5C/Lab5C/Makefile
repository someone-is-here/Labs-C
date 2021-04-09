all: createDir build test

createDir:
	mkdir -p target
build:
	gcc -o target/Source Source.c List1.c -lm
test:
	gcc -o target/test Source.c tests.c List1.c -Dmain=_main -lm
	./target/test