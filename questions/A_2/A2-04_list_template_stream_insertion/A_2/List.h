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

    friend ostream& operator<< <>(ostream& out, const List<T>& list);

   private:
    // Not needed in this question; private so it cannot be used by mistake.
    List(const List<T>& other);
    List<T>& operator=(const List<T>& other);
};

// Template code must be visible to the compiler, so the .cpp files are included here.
// List.cpp holds the given functions. A_2.cpp holds operator<< and is included here like List.cpp.
// A_2.cpp has its own include guard, so it can also be compiled on its own (it is on the g++ line).
#include "List.cpp"
#include "A_2.cpp"

#endif
