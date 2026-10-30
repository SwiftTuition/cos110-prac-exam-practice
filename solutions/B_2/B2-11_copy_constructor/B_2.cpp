#ifndef B_2_CPP
#define B_2_CPP

#include "List.h"

// Copy constructor: builds a deep copy of other, in the same order.
template <class T>
List<T>::List(const List<T>& other) : headNode(NULL), size(0) {
    Node<T>* tail = NULL;              // last node of the new list
    Node<T>* curr = other.headNode;
    while (curr != NULL) {
        // A new node with a new copy of the data.
        Node<T>* newNode = new Node<T>(new T(curr->getData()));
        if (tail == NULL) {
            headNode = newNode;        // first node of the copy
        } else {
            tail->next() = newNode;    // link after the current last node
        }
        tail = newNode;
        size++;
        curr = curr->next();
    }
}

#endif
