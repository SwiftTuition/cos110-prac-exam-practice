#include "Binary.h"

// Sets array[index], array[index + 1], ... from the same positions in bits.
// A '1' gives true; any other character gives false.
void Binary::setBits(string bits, int index) {
    // Invalid input (index < 0), or the end of the array or of the string: stop.
    // The (int) cast stops the signed/unsigned comparison warning (-Werror).
    if (index < 0 || index >= size || index >= (int)bits.length()) {
        return;
    }
    // Set this bit, then the rest.
    array[index] = (bits[index] == '1');
    setBits(bits, index + 1);
}
