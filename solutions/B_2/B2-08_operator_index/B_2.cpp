#ifndef B_2_CPP
#define B_2_CPP

#include "List.h"

// Returns the data in the node at position index (the head is position 0).
// Throws an Exception when index is out of range.
template <class T>
const T& List<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw Exception("Index out of bounds");
    }
    Node<T>* curr = headNode;
    for (int i = 0; i < index; i++) {
        curr = curr->next();
    }
    return curr->getData();
}

#endif
