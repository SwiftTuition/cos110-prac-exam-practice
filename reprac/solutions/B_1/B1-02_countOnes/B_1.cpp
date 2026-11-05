#include "Binary.h"

// Returns the number of 1 bits from index to the end of the array.
int Binary::countOnes(int index) {
    // Invalid index (less than 0) or past the last bit: nothing to count.
    if (index < 0 || index >= size) {
        return 0;
    }
    // Recursive case: this bit (1 or 0) plus the 1 bits after it.
    if (array[index]) {
        return 1 + countOnes(index + 1);
    }
    return countOnes(index + 1);
}
