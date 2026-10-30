#include "HR.h"

HR::HR(int size) : Department(size) {
}

string HR::getName() {
    return "HR";
}

// R12000 per employee per month.
float HR::costToCompany() {
    return countEmployees() * 12000.0f;
}
