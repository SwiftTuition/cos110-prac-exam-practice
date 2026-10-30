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
    // Write this function in A_3.cpp.
    List<T>& operator=(const List<T>& other);

    friend ostream& operator<< <>(ostream& out, const List<T>& list);

   private:
    // Not needed in this question; private so it cannot be used by mistake.
    List(const List<T>& other);
};

#include "List.cpp"
// The function you write in A_3.cpp is a template too, so A_3.cpp is included here (like List.cpp).
// A_3.cpp has its own include guard, so it can also be compiled on its own (it is on the g++ line).
#include "A_3.cpp"

#endif
