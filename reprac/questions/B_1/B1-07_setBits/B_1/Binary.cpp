#include "Binary.h"

// The array is filled by setBits (written in B_1.cpp).
Binary::Binary(string bits) {
    size = (int)bits.length();
    array = new bool[size];
    setBits(bits, 0);
}

Binary::Binary(const Binary& other) {
    size = other.size;
    array = new bool[size];
    for (int i = 0; i < size; i++) {
        array[i] = other.array[i];
    }
}

Binary::~Binary() {
    delete[] array;
}

bool& Binary::operator[](int index) {
    return array[index];
}

const bool& Binary::operator[](int index) const {
    return array[index];
}

int Binary::getSize() const {
    return size;
}

// Prints the bits from index 0 to the end, for example 0101.
ostream& operator<<(ostream& out, const Binary& b) {
    for (int i = 0; i < b.size; i++) {
        out << (b.array[i] ? '1' : '0');
    }
    return out;
}
