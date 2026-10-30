#include "Employee.h"

bool Employee::operator==(const Employee& other) const {
    // Only the ID numbers are compared. Two IDs that are not set ("") are equal too.
    return idNum == other.idNum;
}

bool Employee::operator!=(const Employee& other) const {
    return !(*this == other);
}
