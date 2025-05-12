CC=$(CXX)
GIT_VERSION="$(shell git describe --always)"
CPPFLAGS = -Wall -DGIT_VERSION=\"$(GIT_VERSION)\" #-O3 -funroll-loops

all: randombot runtest

clean:
	rm -rf *.o *.s *~ randombot test

randombot: randombot.o \
           string-util.o

runtest: test
	./test

test: assert.o \
	attack.o \
	check.o \
  color.o \
  fen.o \
  irreversible.o \
  move.o \
  movegen.o \
  point.o \
  piece.o \
  piece-moves.o \
  string-util.o \
  test.o
