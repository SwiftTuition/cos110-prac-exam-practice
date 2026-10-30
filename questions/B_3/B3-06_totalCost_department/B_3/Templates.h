#ifndef TEMPLATES_H
#define TEMPLATES_H

#include "Department.h"
#include "List.h"

using namespace std;

// General template: a list of other things has no cost to the company.
template <class T>
float totalCost(List<T>& list) {
    return 0;
}

// Specialization for T = Department*. Declared here, after the general
// template. Defined in B_3.cpp. Company.cpp uses it too.
template <>
float totalCost<Department*>(List<Department*>& list);

#endif
