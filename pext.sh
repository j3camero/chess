# Compiles an example program to demonstrate the PEXT instruction.
g++ pext.cc -o pext -mbmi2

# Outputs assembly language into a file called pext.s
g++ pext.cc -S -mbmi2
