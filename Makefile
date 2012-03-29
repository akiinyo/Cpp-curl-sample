cc = gcc
GPP = $(CC) -E

all: clean build

build:
	$(GPP) hello_world.cpp -o hello_world

clean:
	rm -f hello_world
