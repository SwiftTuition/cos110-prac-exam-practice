#include "BinaryStrings.h"

// Counts the positive strings from curr to the end of the list.
// A string is positive when its first bit (the sign bit) is 0 and at least one
// later bit is 1. index is the bit of curr that is checked in this call.
int BinaryStrings::calculatePos(Node<Binary>* curr, int index) {
    // Base case: past the last node (this also covers an empty list).
    if (curr == NULL) {
        return 0;
    }
    // Invalid input: index 0 is the sign bit, so the search starts at 1 or later.
    if (index < 1) {
        return 0;
    }
    // This string is not positive: no 1 was found before the end of the string,
    // or the sign bit is 1. The size test comes first, so bit 0 of an empty
    // string is never read. Move to the next node and start again at bit 1.
    if (index >= curr->getData().getSize() || curr->getData()[0]) {
        return calculatePos(curr->next(), 1);
    }
    // A 1 after a 0 sign bit: this string is positive. Count it and move on.
    if (curr->getData()[index]) {
        return 1 + calculatePos(curr->next(), 1);
    }
    // This bit is 0: check the next bit of the same string.
    return calculatePos(curr, index + 1);
}
