#include "Team.h"

int Team::oldest(int index) {
    // Base case: an invalid index, or past the last slot. No employees, so 0.
    if (index < 0 || index >= size) {
        return 0;
    }
    // Recursive case: the oldest age in the slots after this one.
    int restOldest = oldest(index + 1);

    // Compare this slot (if it holds an employee) with the rest.
    if (members[index] != NULL && members[index]->getAge() > restOldest) {
        return members[index]->getAge();
    }
    return restOldest;
}
