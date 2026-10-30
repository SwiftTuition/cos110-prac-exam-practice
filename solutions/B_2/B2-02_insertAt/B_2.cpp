#ifndef B_2_CPP
#define B_2_CPP

#include "List.h"

// Inserts value so that it ends up at index pos (the first node is index 0).
// pos <= 0 adds at the front. pos >= size adds at the back.
template <class T>
void List<T>::insertAt(T value, int pos) {
    Node<T>* newNode = new Node<T>(new T(value));
    // Front: an empty list, or a position of 0 or less.
    if (headNode == NULL || pos <= 0) {
        newNode->next() = headNode;
        headNode = newNode;
        size++;
        return;
    }
    // Move prev to the node just before index pos.
    // If the list runs out first, prev stops at the last node (append).
    Node<T>* prev = headNode;
    int count = 1;
    while (prev->next() != NULL && count < pos) {
        prev = prev->next();
        count++;
    }
    newNode->next() = prev->next();
    prev->next() = newNode;
    size++;
}

#endif
