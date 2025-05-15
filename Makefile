CC=$(CXX)
CPPFLAGS = -Wall #-O3 -funroll-loops

all: randombot runtest

clean:
	rm -rf *.o *.s *~ randombot test

randombot: randombot.o \
           string-util.o

runtest: test
	./test

test: attack.o \
	check.o \
  color.o \
  fen.o \
  irreversible.o \
  move.o \
  movegen.o \
  point.o \
  piece.o piece-test.o \
  piece-moves.o \
  string-util.o string-util-test.o \
  test.o

macro2: macro2.o

macro3: macro3.o
