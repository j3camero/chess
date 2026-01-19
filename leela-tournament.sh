cutechess-cli \
-each proto=uci \
-engine name=lc1 cmd=lc0 tc=1 \
-engine name=lc2 cmd=lc0 tc=2 \
-engine name=lc5 cmd=lc0 tc=5 \
-games 2 \
-openings file=balsa/Balsa_v110221.pgn \
-repeat \
-rounds 1 \
;
