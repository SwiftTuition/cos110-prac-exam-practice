#ifndef B_2_CPP
#define B_2_CPP

#include "List.h"

// Returns the index of the first node that holds value, or -1 if there is none.
template <class T>
int List<T>::indexOf(T value) {
    Node<T>* curr = headNode;
    int index = 0;
    while (curr != NULL) {
        if (curr->getData() == value) {
            return index;   // early exit: the first match wins
        }
        curr = curr->next();
        index++;
    }
    return -1;              // empty list, or not found
}

#endif
