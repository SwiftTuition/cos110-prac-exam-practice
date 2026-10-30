#include "Employee.h"

int Employee::extractIntFromString(string str, int start, int end) {
    if (start < 0 || start >= end || end > (int)str.length()) {
        throw Exception("Invalid range");
    }
    int result = 0;
    for (int i = start; i < end; i++) {
        if (str[i] < '0' || str[i] > '9') {
            throw Exception("Not a digit");
        }
        result = result * 10 + (str[i] - '0');
    }
    return result;
}
