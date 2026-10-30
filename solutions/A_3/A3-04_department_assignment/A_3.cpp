#include "Department.h"

Department& Department::operator=(const Department& other) {
    // 1. Self-assignment check: compare the addresses.
    if (this == &other) {
        return *this;
    }

    // 2. Free the old memory: every team (each team deletes its employees), then the array.
    for (int i = 0; i < size; i++) {
        delete teams[i];
    }
    delete[] teams;

    // 3. Deep copy: a new array, and a new copy of every team.
    size = other.size;
    teams = new Team*[size];
    for (int i = 0; i < size; i++) {
        if (other.teams[i] == NULL) {
            teams[i] = NULL;
        } else {
            teams[i] = new Team(*other.teams[i]);
        }
    }

    // 4. Return the current object so that a = b = c works.
    return *this;
}
