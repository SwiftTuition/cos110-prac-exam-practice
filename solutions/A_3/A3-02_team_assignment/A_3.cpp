#include "Team.h"

Team& Team::operator=(const Team& other) {
    // 1. Self-assignment check: compare the addresses.
    if (this == &other) {
        return *this;
    }

    // 2. Free the old memory: every employee, then the array.
    for (int i = 0; i < size; i++) {
        delete members[i];
    }
    delete[] members;

    // 3. Deep copy: a new array, and a new copy of every employee.
    size = other.size;
    members = new Employee*[size];
    for (int i = 0; i < size; i++) {
        if (other.members[i] == NULL) {
            members[i] = NULL;
        } else {
            members[i] = new Employee(*other.members[i]);
        }
    }

    // 4. Return the current object so that a = b = c works.
    return *this;
}
