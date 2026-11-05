#include "Binary.h"

// Returns the decimal value of the bits from index 0 up to and including index.
// array[0] is the leftmost bit (the most significant bit).
int Binary::toDecimal(int index) {
    // Invalid index, and also the stop case: index -1 means "no bits left".
    if (index < 0 || index >= size) {
        return 0;
    }
    // Recursive case: the value of the bits before index, shifted one place left,
    // plus this bit.
    if (array[index]) {
        return 2 * toDecimal(index - 1) + 1;
    }
    return 2 * toDecimal(index - 1);
}
