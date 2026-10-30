#ifndef B_2_CPP
#define B_2_CPP

#include "List.h"

// Reverses the order of the nodes by turning every link around.
// No node is created or deleted.
template <class T>
void List<T>::reverse() {
    Node<T>* prev = NULL;
    Node<T>* curr = headNode;
    while (curr != NULL) {
        Node<T>* temp = curr->next();   // remember the rest of the list
        curr->next() = prev;            // turn this link around
        prev = curr;
        curr = temp;
    }
    headNode = prev;                    // the old last node is the new head
}

#endif
