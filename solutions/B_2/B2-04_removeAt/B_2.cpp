#ifndef B_2_CPP
#define B_2_CPP

#include "List.h"

// Removes the node at index pos (the first node is index 0).
// Returns false and changes nothing when pos is out of range.
template <class T>
bool List<T>::removeAt(int pos) {
    // Out of range (this also covers an empty list).
    if (pos < 0 || pos >= size) {
        return false;
    }
    // Remove the head.
    if (pos == 0) {
        Node<T>* temp = headNode;
        headNode = headNode->next();
        delete temp;
        size--;
        return true;
    }
    // Move prev to the node just before index pos.
    Node<T>* prev = headNode;
    for (int i = 0; i < pos - 1; i++) {
        prev = prev->next();
    }
    Node<T>* curr = prev->next();
    prev->next() = curr->next();
    delete curr;
    size--;
    return true;
}

#endif
