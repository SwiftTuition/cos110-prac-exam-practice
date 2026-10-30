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

    // Not needed in this question; private so it cannot be used by mistake.
    List(const List<T>& other);
    List<T>& operator=(const List<T>& other);

   public:
    List();
    ~List();
    void prepend(T value);
    Node<T>* const& head() const;
    int getSize();

    friend ostream& operator<< <>(ostream& out, const List<T>& list);
};

#include "List.cpp"

#endif
