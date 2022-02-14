CC=$(CXX)
GIT_VERSION="$(shell git describe --always)"
CPPFLAGS = -Wall -DGIT_VERSION=\"$(GIT_VERSION)\" #-O3 -funroll-loops

all: test uci

clean:
	rm -rf *.o test-main uci

test: test-main
	./test-main

test-main: test-main.o \
           fake-test.o

uci: uci.o
