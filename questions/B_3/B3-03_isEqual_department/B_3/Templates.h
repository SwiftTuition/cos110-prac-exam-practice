#ifndef TEMPLATES_H
#define TEMPLATES_H

#include "Department.h"

using namespace std;

// General template: true when the two values are equal (==).
template <class T>
bool isEqual(T a, T b) {
    return a == b;
}

// Specialization for T = Department*. Declared here, after the general
// template. Defined in B_3.cpp.
template <>
bool isEqual<Department*>(Department* a, Department* b);

#endif
