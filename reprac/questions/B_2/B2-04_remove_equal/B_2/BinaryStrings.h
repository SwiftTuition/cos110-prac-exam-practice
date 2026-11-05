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
    BinaryStrings(const BinaryStrings& other);
    BinaryStrings& operator=(const BinaryStrings& other);

   public:
    BinaryStrings();
    ~BinaryStrings();
    void prepend(const Binary& b);
    Node<Binary>*& getHead();
    int calculatePos();
    int getSize();
    // Removes the first string equal to b. Returns false if there is none.
    // Write this function in B_2.cpp.
    bool remove(const Binary& b);

    friend ostream& operator<<(ostream& out, const BinaryStrings& list);
};

#endif
