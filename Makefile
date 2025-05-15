CC=$(CXX)
CPPFLAGS = -Wall #-O3 -funroll-loops

all: randombot runtest

clean:
	rm -rf *.o *.s *~ randombot test

randombot: randombot.o \
           string-util.o

runtest: test
	./test

test: attack.o attack-test.o \
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
  test.o
