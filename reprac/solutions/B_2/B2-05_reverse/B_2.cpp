#include "BinaryStrings.h"

// Reverses the order of the nodes by turning every link around.
// No node is created or deleted.
void BinaryStrings::reverse() {
    Node<Binary>* prev = NULL;
    Node<Binary>* curr = head;
    while (curr != NULL) {
        Node<Binary>* temp = curr->next();   // remember the rest of the list
        curr->next() = prev;                 // turn this link around
        prev = curr;
        curr = temp;
    }
    // prev is the old last node: it is the new head.
    head = prev;
}
