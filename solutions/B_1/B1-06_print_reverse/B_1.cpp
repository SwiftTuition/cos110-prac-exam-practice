#ifndef B_1_CPP
#define B_1_CPP

#include "List.h"

template <class T>
void List<T>::printReverse(Node<T>* curr) {
    // Base case: past the last node, so there is nothing to print.
    if (curr == NULL) {
        return;
    }
    // Recursive case: print the nodes after this one first, then this node.
    printReverse(curr->next());
    cout << curr->getData() << endl;
}

#endif
