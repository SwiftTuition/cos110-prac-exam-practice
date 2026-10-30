#include "Employee.h"

int Employee::checksum(string id, int index) {
    // Base case: an invalid index, or no digits left. Nothing to add.
    if (index < 0 || index >= (int)id.length()) {
        return 0;
    }
    int digit = id[index] - '0';

    // Double this digit if the number of characters after it is odd.
    // A doubled value of more than 9 becomes that value minus 9.
    if (((int)id.length() - 1 - index) % 2 == 1) {
        digit = digit * 2;
        if (digit > 9) {
            digit = digit - 9;
        }
    }

    // Recursive case: add the sum of the digits after this one.
    return digit + checksum(id, index + 1);
}
