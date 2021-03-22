all: createDir build test

createDir:
	mkdir -p target

build: 
	gcc -o target/fib fib.c
test:
	gcc -o target/test fib.c tests.c -Dmain=_main
	./target/test