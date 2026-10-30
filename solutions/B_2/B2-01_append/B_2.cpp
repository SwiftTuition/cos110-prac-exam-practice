#ifndef B_2_CPP
#define B_2_CPP

#include "List.h"

// Adds value at the end of the list.
template <class T>
void List<T>::append(T value) {
    Node<T>* newNode = new Node<T>(new T(value));
    // Case 1: the list is empty, so the new node becomes the head.
    if (headNode == NULL) {
        headNode = newNode;
        size++;
        return;
    }
    // Case 2: walk to the last node (the node whose next is NULL).
    Node<T>* curr = headNode;
    while (curr->next() != NULL) {
        curr = curr->next();
    }
    curr->next() = newNode;
    size++;
}

#endif
