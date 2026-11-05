#include "Templates.h"

// For a Binary, print the bits and the decimal value, for example: Binary: 0101 (5)
template <>
void printValue<Binary>(const Binary& value) {
    int decimal = 0;
    for (int i = 0; i < value.getSize(); i++) {
        decimal = decimal * 2;
        if (value[i]) {
            decimal = decimal + 1;
        }
    }
    cout << "Binary: " << value << " (" << decimal << ")" << endl;
}
