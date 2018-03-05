CC = gcc
CFLAGS = -Wall
CPPFLAGS = -DHAVE_MATH
LDLIBS = -lm

all: ops

ops: ops.o add.o mul.o

add.o: add.c add.h
mul.o: mul.c mul.h

clean:
	rm -rf *.o ops
