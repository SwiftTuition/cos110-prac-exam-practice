#ifndef BINARY_H
#define BINARY_H

#include <iostream>
#include <string>

using namespace std;

class Binary {
   private:
    bool* array;
    int size;

    // Not needed in this question; private so it cannot be used by mistake.
    Binary& operator=(const Binary& other);

   public:
    Binary(string bits);
    Binary(const Binary& other);
    ~Binary();
    bool& operator[](int index);
    const bool& operator[](int index) const;
    int getSize() const;
    // True when the bits from start to end read the same in both directions.
    // Write this function in B_1.cpp using recursion.
    bool isPalindrome(int start, int end);

    friend ostream& operator<<(ostream& out, const Binary& b);
};

#endif
