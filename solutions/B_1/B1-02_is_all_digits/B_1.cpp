#include "Employee.h"

bool Employee::isAllDigits(string str, int index) {
    // Invalid index: return false.
    if (index < 0 || index > (int)str.length()) {
        return false;
    }
    // Base case: no characters are left to check.
    if (index == (int)str.length()) {
        return true;
    }
    // This character is not a digit.
    if (str[index] < '0' || str[index] > '9') {
        return false;
    }
    // Recursive case: check the rest of the string.
    return isAllDigits(str, index + 1);
}
