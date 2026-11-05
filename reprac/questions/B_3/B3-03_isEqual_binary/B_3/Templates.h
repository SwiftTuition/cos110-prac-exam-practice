#ifndef TEMPLATES_H
#define TEMPLATES_H

#include "Binary.h"

using namespace std;

// General template: true when the two values are equal.
template <class T>
bool isEqual(const T& a, const T& b) {
    return a == b;
}

// Specialisation for Binary (Binary has no operator==). Declared here, after
// the general template and before any use. Defined in B_3.cpp.
template <>
bool isEqual<Binary>(const Binary& a, const Binary& b);

#endif
