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

    // 3. The new size is the number of employees in the other team.
    int count = 0;
    for (int i = 0; i < other.size; i++) {
        if (other.members[i] != NULL) {
            count++;
        }
    }
    size = count;
    members = new Employee*[size];

    // 4. Copy every employee into the next free slot, keeping the order.
    int next = 0;
    for (int i = 0; i < other.size; i++) {
        if (other.members[i] != NULL) {
            members[next] = new Employee(*other.members[i]);
            next++;
        }
    }

    // 5. Return the current object so that a = b = c works.
    return *this;
}
