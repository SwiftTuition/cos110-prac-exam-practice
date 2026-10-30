#ifndef LIST_H
#define LIST_H

#include <iostream>

#include "Node.h"

using namespace std;

// Declared here so that the specialization below can name the type.
class Department;

template <class T>
class List;

template <class T>
ostream& operator<<(ostream& out, const List<T>& list);

// head() is written as Node<T>* const& because the UML form const Node<T>*&
// does not compile once it is called.
template <class T>
class List {
   private:
    Node<T>* headNode;
    int size;

    // Not needed in this question; private so it cannot be used by mistake.
    List(const List<T>& other);
    List<T>& operator=(const List<T>& other);

   public:
    List();
    ~List();
    void prepend(T value);
    Node<T>* const& head() const;
    int getSize();
    void clear();

    friend ostream& operator<< <>(ostream& out, const List<T>& list);
};

// Note in COS 110, for templates, the implementation file is included at the
// bottom of the class declaration. That is why List.cpp is not on the g++ line.
#include "List.cpp"

// Specialization of one member for T = Department*. It is declared here, after
// the general template and before any use. It is defined in B_3.cpp, which is
// compiled once.
template <>
void List<Department*>::clear();

#endif
