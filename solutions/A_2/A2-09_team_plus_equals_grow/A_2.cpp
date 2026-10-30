#include "Team.h"

Team& Team::operator+=(Employee* employee) {
    if (employee == NULL) {
        return *this;
    }
    Employee** temp = new Employee*[size + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = members[i];  // move the pointers; the employees stay where they are
    }
    temp[size] = new Employee(*employee);  // the team keeps its own copy
    delete[] members;                      // only the old array, not the employees
    members = temp;
    size++;
    return *this;
}
