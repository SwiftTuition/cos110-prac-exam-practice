#include "Department.h"

int Department::totalEmployees(int index) {
    // Base case: an invalid index, or past the last slot. Nothing to add.
    if (index < 0 || index >= size) {
        return 0;
    }
    // Employees in this slot (an empty slot adds 0).
    int here = 0;
    if (teams[index] != NULL) {
        here = teams[index]->getMemberCount();
    }
    // Recursive case: add the employees of the remaining slots.
    return here + totalEmployees(index + 1);
}
