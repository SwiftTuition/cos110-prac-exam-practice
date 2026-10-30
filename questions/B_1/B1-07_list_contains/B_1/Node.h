#ifndef NODE_H
#define NODE_H

#include <cstddef>

template <class T>
class Node {
   private:
    T* data;
    Node<T>* nextNode;

   public:
    Node(T* data);
    ~Node();
    const T& getData();
    Node<T>*& next();

   private:
    // Not needed in this question; private so it cannot be used by mistake.
    Node(const Node<T>& other);
    Node<T>& operator=(const Node<T>& other);
};

#include "Node.cpp"

#endif
