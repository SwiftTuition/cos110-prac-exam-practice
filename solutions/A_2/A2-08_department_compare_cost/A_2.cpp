#include "Department.h"

// costToCompany() is virtual, so each department uses its own cost rule.
bool Department::operator<(Department& other) {
    return costToCompany() < other.costToCompany();
}

bool Department::operator>(Department& other) {
    return costToCompany() > other.costToCompany();
}
