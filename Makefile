all: clean build run
clean:
	rm -f serve
build:
	gcc -o serve server.c main.c
run:
	./serve 5555 index.html