#include "Department.h"

Team*& Department::operator[](int index) {
    if (index < 0) {
        throw Exception("Negative index");
    }
    if (index >= size) {
        throw Exception("Index too large");
    }
    // An empty slot is not an error: the caller gets a reference to the NULL pointer.
    return teams[index];
}
