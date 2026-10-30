#ifndef B_2_CPP
#define B_2_CPP

#include "List.h"

// Removes the first node that holds value. Returns true if a node was removed.
template <class T>
bool List<T>::remove(T value) {
    // Case 1: empty list, nothing to remove.
    if (headNode == NULL) {
        return false;
    }
    // Case 2: the head holds the value.
    if (headNode->getData() == value) {
        Node<T>* temp = headNode;
        headNode = headNode->next();
        delete temp;    // ~Node() deletes the data
        size--;
        return true;
    }
    // Case 3: look further, keeping prev one node behind curr.
    // The loop checks curr != NULL first, so a one-node list is safe.
    Node<T>* prev = headNode;
    Node<T>* curr = headNode->next();
    while (curr != NULL) {
        if (curr->getData() == value) {
            prev->next() = curr->next();
            delete curr;
            size--;
            return true;
        }
        prev = curr;
        curr = curr->next();
    }
    // Case 4: not found.
    return false;
}

#endif
