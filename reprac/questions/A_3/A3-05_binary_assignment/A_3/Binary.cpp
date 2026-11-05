#include "Binary.h"

// Each '1' becomes true; any other character becomes false.
Binary::Binary(string bits) {
    size = (int)bits.length();
    array = new bool[size];
    for (int i = 0; i < size; i++) {
        array[i] = (bits[i] == '1');
    }
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

ostream& operator<<(ostream& out, const Binary& b) {
    for (int i = 0; i < b.size; i++) {
        out << (b.array[i] ? '1' : '0');
    }
    return out;
}
