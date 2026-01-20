cutechess-cli \
-each tc=5 timemargin=10 \
-engine name=stockfish cmd=stockfish proto=uci \
-engine name=caissa cmd=~/Caissa/build/bin/caissa proto=uci \
-engine name=viridithas cmd=~/viridithas/viridithas-19.0.1-linux-x86-64-v4 proto=uci \
-engine name=starzix cmd=~/starzix/starzix-6.1-avx2 proto=uci \
-games 2 \
-openings file=balsa/Balsa_v110221.pgn \
-ratinginterval 1 \
-repeat \
-rounds 100 \
;
