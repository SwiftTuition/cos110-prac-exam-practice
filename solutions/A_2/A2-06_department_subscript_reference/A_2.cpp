#include "Department.h"

Team*& Department::operator[](int index) {
    if (index < 0 || index >= size) {
        throw Exception("Index out of bounds");
    }
    // Return the slot itself (not a copy), so the caller can change what it points to.
    return teams[index];
}
