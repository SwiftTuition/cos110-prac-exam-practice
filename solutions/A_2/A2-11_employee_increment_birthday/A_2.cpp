#include "Employee.h"

// Prefix: ++e
Employee& Employee::operator++() {
    age++;
    return *this;
}

// Postfix: e++ (the int parameter only tells the two versions apart)
Employee Employee::operator++(int) {
    Employee old(*this);
    age++;
    return old;
}
