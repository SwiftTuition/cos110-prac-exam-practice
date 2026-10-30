#ifndef B_1_CPP
#define B_1_CPP

#include "List.h"

template <class T>
bool List<T>::contains(Node<T>* curr, T value) {
    // Base case: past the last node, so the value is not in the list.
    if (curr == NULL) {
        return false;
    }
    // Base case: this node holds the value.
    if (curr->getData() == value) {
        return true;
    }
    // Recursive case: search the nodes after this one.
    return contains(curr->next(), value);
}

#endif
