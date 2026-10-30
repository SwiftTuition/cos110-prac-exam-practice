#ifndef A_3_CPP
#define A_3_CPP

#include "List.h"

template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
    // 1. Self-assignment check: compare the addresses.
    if (this == &other) {
        return *this;
    }

    // 2. Free the old nodes. Each node deletes its own data.
    Node<T>* curr = headNode;
    while (curr != NULL) {
        Node<T>* temp = curr;
        curr = curr->next();
        delete temp;
    }
    headNode = NULL;
    size = 0;

    // 3. Copy the other list node by node, keeping the order.
    //    tail is the last node of this list, so each new node goes at the end.
    Node<T>* tail = NULL;
    Node<T>* otherCurr = other.headNode;
    while (otherCurr != NULL) {
        Node<T>* newNode = new Node<T>(new T(otherCurr->getData()));
        if (tail == NULL) {
            headNode = newNode;
        } else {
            tail->next() = newNode;
        }
        tail = newNode;
        size++;
        otherCurr = otherCurr->next();
    }

    // 4. Return the current object so that a = b = c works.
    return *this;
}

#endif
