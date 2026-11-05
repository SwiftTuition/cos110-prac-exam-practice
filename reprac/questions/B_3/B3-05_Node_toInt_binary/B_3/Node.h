#ifndef NODE_H
#define NODE_H

#include <iostream>

#include "Binary.h"

using namespace std;

template <class T>
class Node {
   private:
    T data;
    Node<T>* nextNode;

   public:
    Node(T data);
    ~Node();
    T& getData();
    Node<T>*& next();
    int toInt();
};

// Note in COS 110, for templates, the implementation file is included at the
// bottom of the class declaration. That is why Node.cpp is not on the g++ line.
#include "Node.cpp"

// Specialisation of one member for T = Binary. It is declared here, after the
// general template and before any use. It is defined in B_3.cpp, which is
// compiled once.
template <>
int Node<Binary>::toInt();

#endif
