CC=$(CXX)
GIT_VERSION="$(shell git describe --always)"
CPPFLAGS = -Wall -DGIT_VERSION=\"$(GIT_VERSION)\" #-O3 -funroll-loops

all: randombot test

clean:
	rm -rf *.o *~ randombot test-main

randombot: randombot.o \
           string-util.o

test: test-main
	./test-main

test-main: board.o board-test.o \
           string-util.o string-util-test.o \
           test-main.o \
           fake-test.o
