#include "BinaryStrings.h"

// Inserts a copy of b so that it becomes the node at position pos (the head is position 0).
// pos <= 0 inserts at the front. A pos past the end appends.
void BinaryStrings::insertAt(const Binary& b, int pos) {
    Node<Binary>* newNode = new Node<Binary>(b);
    // Front case: also covers the empty list.
    if (pos <= 0 || head == NULL) {
        newNode->next() = head;
        head = newNode;
        size++;
        return;
    }
    // Walk to the node before position pos, or to the last node.
    Node<Binary>* prev = head;
    int count = 1;
    while (prev->next() != NULL && count < pos) {
        prev = prev->next();
        count++;
    }
    // Link the new node in after prev.
    newNode->next() = prev->next();
    prev->next() = newNode;
    size++;
}
