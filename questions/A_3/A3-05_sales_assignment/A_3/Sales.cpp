#include "Sales.h"

// A new Sales department starts with a target of 0.
Sales::Sales(int size) : Department(size), target(0) {
}

void Sales::setTarget(int target) {
    this->target = target;
}

int Sales::getTarget() {
    return target;
}

string Sales::getName() {
    return "Sales";
}

// R15000 per employee per month.
float Sales::costToCompany() {
    return countEmployees() * 15000.0f;
}
