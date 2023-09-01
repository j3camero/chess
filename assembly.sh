# This script compiles all the C++ files into assembly language.
GIT_VERSION="$(git describe --always)"
BASIC_FLAGS="-Wall -DGIT_VERSION=\"$GIT_VERSION\""
OPTIMIZATION_FLAGS="-O3 -funroll-loops"
CPPFLAGS="$BASIC_FLAGS"
echo "CPPFLAGS=$CPPFLAGS"
for i in *.cc; do
    [ -f "$i" ] || break
    echo "Compiling $i"
    g++ -S $CPPFLAGS $i
done
