// An example C++ program to investigate how the copy-constructor
// for small structs works.
//
// Question: does the resulting assembly code copy
// byte-sized fields one-by-one or does it pack them into a
// machine word to copy them all together at once?
//
// Answer: it appears the g++ compiler is smart enough to copy
// the four byte-sized fields in FourChars together as a
// word-sized unit rather than one-by-one as individual bytes.

struct FourChars {
  char a;
  char b;
  char c;
  char d;
};

struct FiveChars {
  char a;
  char b;
  char c;
  char d;
  char e;
};

int main() {
  FourChars a = {3, 5, 7, 11};
  FourChars b;
  b = a;
  FiveChars c = {3, 5, 7, 11, 13};
  FiveChars d;
  d = c;
  return 0;
}
