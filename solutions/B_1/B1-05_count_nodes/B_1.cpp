#ifndef B_1_CPP
#define B_1_CPP

#include "List.h"

template <class T>
int List<T>::countNodes(Node<T>* curr) {
    // Base case: past the last node, so there is nothing to count.
    if (curr == NULL) {
        return 0;
    }
    // Recursive case: this node, plus the nodes after it.
    return 1 + countNodes(curr->next());
}

#endif
