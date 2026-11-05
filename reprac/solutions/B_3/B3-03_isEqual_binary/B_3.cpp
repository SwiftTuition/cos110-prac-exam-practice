#include "Templates.h"

// Two Binary objects are equal when they have the same size and the same bit at
// every index. (Binary has no operator==, so the general template cannot be used.)
template <>
bool isEqual<Binary>(const Binary& a, const Binary& b) {
    if (a.getSize() != b.getSize()) {
        return false;
    }
    for (int i = 0; i < a.getSize(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}
