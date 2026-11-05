#include "BinaryStrings.h"

// Adds a copy of b at the end of the list.
void BinaryStrings::append(const Binary& b) {
    // The node makes its own copy of b (Node<Binary> stores a Binary).
    Node<Binary>* newNode = new Node<Binary>(b);
    if (head == NULL) {
        // Empty list: the new node is the only node.
        head = newNode;
    } else {
        // Walk to the last node: the node whose next() is NULL.
        Node<Binary>* curr = head;
        while (curr->next() != NULL) {
            curr = curr->next();
        }
        curr->next() = newNode;
    }
    size++;
}
