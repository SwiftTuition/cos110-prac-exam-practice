#ifndef LIST_H
#define LIST_H

#include <iostream>

#include "Node.h"

using namespace std;

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
    bool remove(T value);

    friend ostream& operator<< <>(ostream& out, const List<T>& list);
};

// Note in COS 110, for templates, the implementation file is included at the
// bottom of the class declaration. List.cpp holds the given functions.
#include "List.cpp"

#endif
