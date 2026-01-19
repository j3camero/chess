cutechess-cli \
-each proto=uci tc=5 \
-engine name=stockfish2k cmd=stockfish nodes=2000 \
-engine name=stockfish1k cmd=stockfish nodes=1000 \
-engine name=stockfish100 cmd=stockfish nodes=100 \
-engine name=material-count-depth-4 cmd=./material-count-depth-4 \
-engine name=material-count-depth-3 cmd=./material-count-depth-3 \
-engine name=material-count-depth-2 cmd=./material-count-depth-2 \
-engine name=material-count-depth-1 cmd=./material-count-depth-1 \
-engine name=randombot cmd=./randombot \
-games 2 \
-openings file=balsa/Balsa_v110221.pgn \
-rounds 1 \
;
#-engine name=stockfish10k cmd=stockfish nodes=10000 \
#-engine name=stockfish5k cmd=stockfish nodes=5000 \
#-engine name=stockfish4k cmd=stockfish nodes=4000 \
#-engine name=stockfish3k cmd=stockfish nodes=3000 \
