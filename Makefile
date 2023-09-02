CC=$(CXX)
GIT_VERSION="$(shell git describe --always)"
CPPFLAGS = -Wall -DGIT_VERSION=\"$(GIT_VERSION)\" #-O3 -funroll-loops

all: randombot test

clean:
	rm -rf *.o *.s *~ randombot test-main

randombot: randombot.o \
           string-util.o

test: test-main
	./test-main

test-main: attack.o attack-test.o \
           check.o check-test.o \
           color.o color-test.o \
           fen.o fen-test.o \
           irreversible.o irreversible-test.o \
           move.o move-test.o \
           movegen.o movegen-test.o \
           point.o point-test.o \
           piece.o piece-test.o \
           piece-moves.o \
           string-util.o string-util-test.o \
           test-main.o
