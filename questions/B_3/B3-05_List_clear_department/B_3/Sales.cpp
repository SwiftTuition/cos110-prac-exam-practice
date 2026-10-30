#include "Sales.h"

Sales::Sales(int size) : Department(size) {
}

string Sales::getName() {
    return "Sales";
}

// Assumed rule: R15000 per employee per month.
float Sales::costToCompany() {
    return countEmployees() * 15000.0f;
}
