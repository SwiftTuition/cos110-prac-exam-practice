#include "Templates.h"

// For two Binary objects, the larger one is the one with the larger decimal value.
// If the values are equal, return a.
template <>
Binary largest<Binary>(Binary a, Binary b) {
    int valueA = 0;
    for (int i = 0; i < a.getSize(); i++) {
        valueA = valueA * 2;
        if (a[i]) {
            valueA = valueA + 1;
        }
    }
    int valueB = 0;
    for (int i = 0; i < b.getSize(); i++) {
        valueB = valueB * 2;
        if (b[i]) {
            valueB = valueB + 1;
        }
    }
    if (valueB > valueA) {
        return b;
    }
    return a;
}
