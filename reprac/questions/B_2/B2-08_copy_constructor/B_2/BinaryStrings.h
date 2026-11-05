#ifndef BINARYSTRINGS_H
#define BINARYSTRINGS_H

#include <iostream>

#include "Binary.h"
#include "Node.h"

using namespace std;

class BinaryStrings {
   private:
    Node<Binary>* head;
    int size;

    // Not needed in this question; private so it cannot be used by mistake.
    BinaryStrings& operator=(const BinaryStrings& other);

   public:
    BinaryStrings();
    ~BinaryStrings();
    void prepend(const Binary& b);
    Node<Binary>*& getHead();
    int calculatePos();
    int getSize();
    // Deep copy: the new list has its own nodes with the same strings in the same order.
    // Write this function in B_2.cpp.
    BinaryStrings(const BinaryStrings& other);

    friend ostream& operator<<(ostream& out, const BinaryStrings& list);
};

#endif
