#include "Node.h"

// Specialisation of one member: for a Node<Binary>, toInt() returns the decimal
// value of the stored binary string (data[0] is the most significant bit).
template <>
int Node<Binary>::toInt() {
    int value = 0;
    for (int i = 0; i < data.getSize(); i++) {
        value = value * 2;
        if (data[i]) {
            value = value + 1;
        }
    }
    return value;
}
