#ifndef LIST_H
#define LIST_H

#include <iostream>

#include "Node.h"

using namespace std;

template <class T>
class List;

template <class T>
ostream& operator<<(ostream& out, const List<T>& list);

template <class T>
class List {
   private:
    Node<T>* headNode;
    int size;

   public:
    List();
    ~List();
    void prepend(T value);
    Node<T>* const& head() const;
    int getSize();
    // Returns true if value is in curr or in any node after curr.
    // Write this function in B_1.cpp using recursion.
    bool contains(Node<T>* curr, T value);

    friend ostream& operator<< <>(ostream& out, const List<T>& list);

   private:
    // Not needed in this question; private so it cannot be used by mistake.
    List(const List<T>& other);
    List<T>& operator=(const List<T>& other);
};

#include "List.cpp"
// The function you write in B_1.cpp is a template too, so B_1.cpp is included here (like List.cpp).
// B_1.cpp has its own include guard, so it can also be compiled on its own (it is on the g++ line).
#include "B_1.cpp"

#endif
