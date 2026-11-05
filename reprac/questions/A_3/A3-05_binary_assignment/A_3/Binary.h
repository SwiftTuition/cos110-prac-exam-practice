#ifndef BINARY_H
#define BINARY_H

#include <iostream>
#include <string>

using namespace std;

class Binary {
   private:
    bool* array;
    int size;

   public:
    Binary(string bits);
    Binary(const Binary& other);
    ~Binary();
    Binary& operator=(const Binary& other);
    bool& operator[](int index);
    const bool& operator[](int index) const;
    int getSize() const;

    friend ostream& operator<<(ostream& out, const Binary& b);
};

#endif
