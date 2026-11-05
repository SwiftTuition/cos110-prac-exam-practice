#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <iostream>

#include "Binary.h"

using namespace std;

// General template: prints any value that has an operator<<.
template <class T>
void printValue(const T& value) {
    cout << "Value: " << value << endl;
}

// Specialisation for Binary. Declared here, after the general template and
// before any use. Defined in B_3.cpp.
template <>
void printValue<Binary>(const Binary& value);

#endif
