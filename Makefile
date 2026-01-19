CC=$(CXX)
CPPFLAGS = -Wall -O3 -funroll-loops

BINARY_TARGETS = material-count-depth-1 \
                 material-count-depth-2 \
                 material-count-depth-3 \
                 material-count-depth-4 \
                 perft-benchmark \
                 perft-marcelk-suite \
                 randombot \
				 runtest \
				 test

CHESS_RULES = attack.o \
              board.o \
              check.o \
              color.o \
              fen.o \
              irreversible.o \
              makemove.o \
              move.o \
              movegen.o \
              perft.o \
              point.o \
              piece.o \
              piece-moves.o \
              string-util.o

UNIT_TESTS = attack-test.o \
	         board-test.o \
             check-test.o \
             color-test.o \
             fen-test.o \
             irreversible-test.o \
             makemove-test.o \
             move-test.o \
             movegen-test.o \
             perft-marcelk-test.o \
             perft-test.o \
             point-test.o \
             piece-test.o \
             string-util-test.o

all: $(BINARY_TARGETS)

clean:
	rm -rf *.o *.s *~ $(BINARY_TARGETS)

material-count-depth-1: material-count-depth-1.o material-count.o $(CHESS_RULES)

material-count-depth-2: material-count-depth-2.o material-count.o $(CHESS_RULES)

material-count-depth-3: material-count-depth-3.o material-count.o $(CHESS_RULES)

material-count-depth-4: material-count-depth-4.o material-count.o $(CHESS_RULES)

perft-benchmark: perft-benchmark.o $(CHESS_RULES)

perft-marcelk-suite: perft-marcelk-suite.o $(CHESS_RULES)

randombot: randombot.o $(CHESS_RULES)

runtest: test
	./test

test: test.o $(CHESS_RULES) $(UNIT_TESTS)
