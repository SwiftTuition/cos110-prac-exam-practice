#include "Templates.h"

// Two departments are equal when they cost the company the same amount.
template <>
bool isEqual<Department*>(Department* a, Department* b) {
    if (a == NULL && b == NULL) {
        return true;
    }
    if (a == NULL || b == NULL) {
        return false;
    }
    return a->costToCompany() == b->costToCompany();
}
