CC=$(CXX)
CPPFLAGS = -Wall #-O3 -funroll-loops

all: perft-benchmark randombot runtest

clean:
	rm -rf *.o *.s *~ randombot test

perft-benchmark: attack.o \
	board.o \
	check.o \
  color.o \
  fen.o \
  irreversible.o \
	makemove.o \
  move.o \
  movegen.o \
	perft.o \
	perft-benchmark.o \
  point.o \
  piece.o \
  piece-moves.o \
  string-util.o

randombot: randombot.o \
           string-util.o

runtest: test
	./test

test: attack.o attack-test.o \
	board.o board-test.o \
	check.o check-test.o \
  color.o color-test.o \
  fen.o fen-test.o \
  irreversible.o irreversible-test.o \
	makemove.o makemove-test.o \
  move.o move-test.o \
  movegen.o movegen-test.o \
	perft.o perft-test.o \
  point.o point-test.o \
  piece.o piece-test.o \
  piece-moves.o \
  string-util.o string-util-test.o \
  test.o
