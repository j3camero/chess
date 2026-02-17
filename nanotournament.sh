cutechess-cli \
-each tc=1 timemargin=10 \
-engine name=fruit cmd=fruit proto=uci \
-engine name=toga2 cmd=toga2 proto=uci \
-engine name=fairymax cmd=fairymax proto=xboard \
-engine name=glaurung cmd=glaurung proto=uci \
-engine name=hoichess cmd=hoichess proto=xboard \
-engine name=fairy-stockfish cmd=fairy-stockfish proto=uci \
-engine name=crafty cmd=crafty proto=xboard \
-engine name=sjeng cmd=sjeng proto=xboard \
-engine name=phalanx cmd=phalanx proto=xboard \
-engine name=sjaakii cmd=sjaakii proto=uci \
-engine name=stockfish-depth-3 cmd=stockfish proto=uci depth=3 \
-engine name=stockfish-depth-2 cmd=stockfish proto=uci depth=2 \
-engine name=stockfish-depth-1 cmd=stockfish proto=uci depth=1 \
-engine name=material-count-depth-4 cmd=./material-count-depth-4 proto=uci \
-engine name=material-count-depth-3 cmd=./material-count-depth-3 proto=uci \
-engine name=material-count-depth-2 cmd=./material-count-depth-2 proto=uci \
-engine name=material-count-depth-1 cmd=./material-count-depth-1 proto=uci \
-engine name=randombot cmd=./randombot proto=uci \
-games 2 \
-openings file=balsa/Balsa_v110221.pgn \
-ratinginterval 1 \
-repeat \
-rounds 10 \
;
#-engine name=lc0 cmd=lc0 proto=uci \
