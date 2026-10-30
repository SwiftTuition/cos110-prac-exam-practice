#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <iostream>

#include "Department.h"

using namespace std;

// General template: prints any value that has a stream insertion operator,
// followed by a newline.
template <class T>
void printItem(const T& item) {
    cout << item << endl;
}

// Specialization for T = Department*. It is declared here, after the general
// template and before any call, so every file that includes Templates.h uses it.
// It is defined in B_3.cpp.
template <>
void printItem<Department*>(Department* const& item);

#endif
