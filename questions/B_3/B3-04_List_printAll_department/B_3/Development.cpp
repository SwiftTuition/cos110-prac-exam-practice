#include "Development.h"

Development::Development(int size) : Department(size) {
}

string Development::getName() {
    return "Development";
}

// Assumed rule: R25000 per employee per month.
float Development::costToCompany() {
    return countEmployees() * 25000.0f;
}
