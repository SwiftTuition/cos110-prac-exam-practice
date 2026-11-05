#include "BinaryStrings.h"

// Deep copy: the new list gets its own nodes, with copies of the same strings in
// the same order. The two lists share no node and no bool array.
BinaryStrings::BinaryStrings(const BinaryStrings& other) : head(NULL), size(0) {
    Node<Binary>* tail = NULL;          // last node of the new list
    Node<Binary>* curr = other.head;
    while (curr != NULL) {
        // The new node makes its own copy of the Binary (deep copy of the array).
        Node<Binary>* newNode = new Node<Binary>(curr->getData());
        if (tail == NULL) {
            head = newNode;             // first node of the new list
        } else {
            tail->next() = newNode;     // link after the current last node
        }
        tail = newNode;
        size++;
        curr = curr->next();
    }
}
