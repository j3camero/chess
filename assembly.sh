GIT_VERSION="$(git describe --always)"
CPPFLAGS="-Wall -DGIT_VERSION=\"$GIT_VERSION\""
#CPPFLAGS="-Wall -DGIT_VERSION=\"$GIT_VERSION\" -O3 -funroll-loops"
echo "CPPFLAGS=$CPPFLAGS"
for i in *.cc; do
    [ -f "$i" ] || break
    echo "Compiling $i"
    g++ -S $CPPFLAGS $i
done
