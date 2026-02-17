#include <iostream>
#include <cstdint>
#include <immintrin.h>

using namespace std;

int main() {
    uint64_t source_value = 0x0123456789ABCDEF;
    uint64_t mask_value   = 0xF000000F0000F00F;
    uint64_t extracted_bits = _pext_u64(source_value, mask_value);
    cout << "Original: 0x" << hex << source_value << endl;
    cout << "Mask:     0x" << hex << mask_value << endl;
    cout << "Extracted: 0x" << hex << extracted_bits << endl;
    return 0;
}
