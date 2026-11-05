#include "BinaryStrings.h"

// Returns the number of positive binary strings in the list.
// A string is positive when its first bit (the sign bit) is 0 and at least one
// other bit is 1.
int BinaryStrings::calculatePos() {
    int count = 0;
    Node<Binary>* curr = head;
    while (curr != NULL) {
        Binary& b = curr->getData();
        // The size test comes first: an empty string has no bit 0 to read.
        if (b.getSize() > 0 && b[0] == false) {
            // Look for a 1 after the sign bit. Count the string once, then stop looking.
            for (int i = 1; i < b.getSize(); i++) {
                if (b[i]) {
                    count++;
                    break;
                }
            }
        }
        curr = curr->next();
    }
    return count;
}
