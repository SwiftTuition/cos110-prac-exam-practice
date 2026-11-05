#include "Binary.h"

Binary& Binary::operator=(const Binary& other) {
    if (this == &other) {
        return *this;
    }

    delete[] array;

    size = other.size;
    array = new bool[size];
    for (int i = 0; i < size; i++) {
        array[i] = other.array[i];
    }

    return *this;
}
