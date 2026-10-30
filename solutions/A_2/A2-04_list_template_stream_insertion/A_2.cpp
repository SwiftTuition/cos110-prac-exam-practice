#ifndef A_2_CPP
#define A_2_CPP

#include "List.h"

template <class T>
ostream& operator<<(ostream& out, const List<T>& list) {
    if (list.headNode == NULL) {
        out << "Empty List";
        return out;
    }
    Node<T>* curr = list.headNode;
    // Stop at the last node, so that no "->" is printed after it.
    while (curr->next() != NULL) {
        out << curr->getData() << "->";
        curr = curr->next();
    }
    out << curr->getData();
    return out;
}

#endif
