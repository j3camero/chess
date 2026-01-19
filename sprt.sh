cutechess-cli \
-each proto=uci tc=60 \
-engine name=stockfish1k cmd=stockfish nodes=1000 \
-engine name=stockfish100 cmd=stockfish nodes=100 \
-games 2 \
-openings file=balsa/Balsa_v110221.pgn \
-repeat \
-rounds 1000 \
-sprt elo0=0 elo1=5 alpha=0.05 beta=0.05 \
;
