#ifndef B_2_CPP
#define B_2_CPP

#include "List.h"

// Sorts the list in ascending order by relinking the nodes (insertion sort).
// The data cannot be changed, so whole nodes are moved instead.
template <class T>
void List<T>::sort() {
    Node<T>* sorted = NULL;           // head of the sorted part
    Node<T>* curr = headNode;
    while (curr != NULL) {
        Node<T>* temp = curr->next(); // remember the rest of the unsorted part
        // Case 1: curr goes in front of the sorted part.
        if (sorted == NULL || curr->getData() < sorted->getData()) {
            curr->next() = sorted;
            sorted = curr;
        } else {
            // Case 2: find the last sorted node that is <= curr, and link curr after it.
            Node<T>* prev = sorted;
            while (prev->next() != NULL && prev->next()->getData() <= curr->getData()) {
                prev = prev->next();
            }
            curr->next() = prev->next();
            prev->next() = curr;
        }
        curr = temp;
    }
    headNode = sorted;
}

#endif
