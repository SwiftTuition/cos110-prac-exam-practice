#include "Team.h"

int Team::countMembers(int index) {
    // Base case: an invalid index, or past the last slot. Nothing to count.
    if (index < 0 || index >= size) {
        return 0;
    }
    // Count this slot if it holds an employee.
    int here = 0;
    if (members[index] != NULL) {
        here = 1;
    }
    // Recursive case: add the count of the remaining slots.
    return here + countMembers(index + 1);
}
