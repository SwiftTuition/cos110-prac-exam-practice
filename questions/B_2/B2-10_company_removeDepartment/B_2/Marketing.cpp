#include "Marketing.h"

Marketing::Marketing(int size) : Department(size) {
}

string Marketing::getName() {
    return "Marketing";
}

// Assumed rule: R18000 per employee per month.
float Marketing::costToCompany() {
    return countEmployees() * 18000.0f;
}
