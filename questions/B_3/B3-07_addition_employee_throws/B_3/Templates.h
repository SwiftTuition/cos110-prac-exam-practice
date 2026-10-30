#ifndef TEMPLATES_H
#define TEMPLATES_H

#include "Employee.h"
#include "Exception.h"

using namespace std;

// General template (L19): adds two values. The result has the type of the first.
template <class T, class U>
T addition(T v1, U v2) {
    return v1 + v2;
}

// Specialization for two Employees. Declared here, after the general template.
// Defined in B_3.cpp.
template <>
Employee addition<Employee, Employee>(Employee v1, Employee v2);

#endif
