#include "Sales.h"

Sales& Sales::operator=(const Sales& other) {
    // 1. Self-assignment check: compare the addresses.
    if (this == &other) {
        return *this;
    }
    // 2. The base class copies its own part (the teams and the size).
    Department::operator=(other);
    // 3. Copy the member that Sales adds.
    target = other.target;
    // 4. Return the current object so that a = b = c works.
    return *this;
}
