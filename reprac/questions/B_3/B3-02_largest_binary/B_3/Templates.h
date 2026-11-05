#ifndef TEMPLATES_H
#define TEMPLATES_H

#include "Binary.h"

using namespace std;

// General template: returns the larger of two values (a if they are equal).
template <class T>
T largest(T a, T b) {
    if (b > a) {
        return b;
    }
    return a;
}

// Specialisation for Binary. Declared here, after the general template and
// before any use. Defined in B_3.cpp.
template <>
Binary largest<Binary>(Binary a, Binary b);

#endif
