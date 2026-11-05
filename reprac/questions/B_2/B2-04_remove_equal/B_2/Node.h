#ifndef NODE_H
#define NODE_H

#include <iostream>


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
};

// Note in COS 110, for templates, the implementation file is included at the
// bottom of the class declaration. That is why Node.cpp is not on the g++ line.
#include "Node.cpp"

#endif
