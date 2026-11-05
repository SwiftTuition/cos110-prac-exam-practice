#ifndef TEMPLATES_H
#define TEMPLATES_H

#include "Binary.h"

using namespace std;

// General template (L19): adds two values. The result has the type of the first.
template <class T, class U>
T addition(T v1, U v2) {
    return v1 + v2;
}

// Specialisation for two Binary objects. Declared here, after the general
// template and before any use. Defined in B_3.cpp.
template <>
Binary addition<Binary, Binary>(Binary v1, Binary v2);

#endif
