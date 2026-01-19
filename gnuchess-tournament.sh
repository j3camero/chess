cutechess-cli \
-engine name=gnuchess8 cmd=gnuchess proto=xboard tc=8 \
-engine name=gnuchess5 cmd=gnuchess proto=xboard tc=5 \
-engine name=gnuchess2 cmd=gnuchess proto=xboard tc=2 \
-engine name=gnuchess1 cmd=gnuchess proto=xboard tc=1 \
-games 2 \
-openings file=balsa/Balsa_v110221.pgn \
-repeat \
-rounds 2 \
;
