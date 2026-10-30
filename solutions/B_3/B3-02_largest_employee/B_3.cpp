#include "Templates.h"

// For employees, the "largest" one is the older one. Same age: return b,
// like the general template does when the values are equal.
template <>
Employee largest<Employee>(Employee a, Employee b) {
    if (a.getAge() > b.getAge()) {
        return a;
    }
    return b;
}
