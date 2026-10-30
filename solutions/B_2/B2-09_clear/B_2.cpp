#ifndef B_2_CPP
#define B_2_CPP

#include "List.h"

// Deletes every node. The list is empty afterwards and can be used again.
template <class T>
void List<T>::clear() {
    Node<T>* curr = headNode;
    while (curr != NULL) {
        Node<T>* temp = curr;      // never delete the loop variable itself
        curr = curr->next();
        delete temp;               // ~Node() deletes the data
    }
    headNode = NULL;
    size = 0;
}

#endif
