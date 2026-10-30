#include "Employee.h"

Employee& Employee::operator=(const Employee& other) {
    // 1. Self-assignment check: compare the addresses.
    if (this == &other) {
        return *this;
    }
    // 2. Free the old memory: Employee has no pointers, so there is nothing to delete.
    // 3. Copy every attribute from the other employee.
    firstName = other.firstName;
    surName = other.surName;
    age = other.age;
    gender = other.gender;
    idNum = other.idNum;
    // 4. Return the current object so that a = b = c works.
    return *this;
}
