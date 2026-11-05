#ifndef NODE_CPP
#define NODE_CPP

#include "Node.h"

// The node keeps its own copy of the data (data is a T, not a T*).
template <class T>
Node<T>::Node(T data) : data(data), nextNode(NULL) {
}

// Deleting a node does not delete the next node.
template <class T>
Node<T>::~Node() {
}

template <class T>
T& Node<T>::getData() {
    return data;
}

template <class T>
Node<T>*& Node<T>::next() {
    return nextNode;
}

#endif
