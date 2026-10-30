#include "Employee.h"

int Employee::extractIntFromString(string str, int start, int end) {
    // Invalid range: return -1.
    if (start < 0 || start >= end || end > (int)str.length()) {
        return -1;
    }
    // The last character of the range must be a digit.
    if (str[end - 1] < '0' || str[end - 1] > '9') {
        return -1;
    }
    int lastDigit = str[end - 1] - '0';

    // Base case: the range has one character.
    if (end - start == 1) {
        return lastDigit;
    }

    // Recursive case: read the range without its last character.
    int front = extractIntFromString(str, start, end - 1);
    if (front == -1) {
        return -1;
    }
    return front * 10 + lastDigit;
}
