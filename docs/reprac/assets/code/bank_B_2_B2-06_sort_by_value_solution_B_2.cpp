#include "BinaryStrings.h"

// Helper (allowed in B_2): the decimal value of a binary string.
// array[0] is the leftmost, most significant bit. An empty string has value 0.
static int decimalValue(const Binary& b) {
    int value = 0;
    for (int i = 0; i < b.getSize(); i++) {
        value = value * 2;
        if (b[i]) {
            value = value + 1;
        }
    }
    return value;
}

// Sorts the strings by decimal value, smallest first, by relinking the nodes
// (insertion sort). Strings with equal values keep their original order.
void BinaryStrings::sort() {
    Node<Binary>* sorted = NULL;            // head of the sorted part
    Node<Binary>* curr = head;
    while (curr != NULL) {
        Node<Binary>* temp = curr->next();  // remember the rest of the unsorted part
        int value = decimalValue(curr->getData());
        // Case 1: curr goes in front of the sorted part.
        if (sorted == NULL || value < decimalValue(sorted->getData())) {
            curr->next() = sorted;
            sorted = curr;
        } else {
            // Case 2: find the last sorted node with a value <= curr's value,
            // and link curr after it.
            Node<Binary>* prev = sorted;
            while (prev->next() != NULL && decimalValue(prev->next()->getData()) <= value) {
                prev = prev->next();
            }
            curr->next() = prev->next();
            prev->next() = curr;
        }
        curr = temp;
    }
    head = sorted;
}
