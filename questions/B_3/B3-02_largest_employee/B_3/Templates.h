#ifndef TEMPLATES_H
#define TEMPLATES_H

#include "Employee.h"

using namespace std;

// General template: returns the larger value. If they are equal, returns b.
template <class T>
T largest(T a, T b) {
    if (a > b) {
        return a;
    }
    return b;
}

// Specialization for T = Employee (Employee has no > operator).
// Declared here, after the general template. Defined in B_3.cpp.
template <>
Employee largest<Employee>(Employee a, Employee b);

#endif
