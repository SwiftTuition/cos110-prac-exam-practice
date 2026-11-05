#include "BinaryStrings.h"

// Counts the strings from curr to the end of the list whose first bit is 1.
int BinaryStrings::countNegative(Node<Binary>* curr) {
    // Base case: past the last node (this also covers an empty list).
    if (curr == NULL) {
        return 0;
    }
    // The size test comes first: an empty string has no bit 0 to read.
    if (curr->getData().getSize() > 0 && curr->getData()[0]) {
        return 1 + countNegative(curr->next());
    }
    return countNegative(curr->next());
}
