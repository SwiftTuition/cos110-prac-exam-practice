#include "Team.h"

const Employee& Team::operator[](int index) const {
    if (index < 0 || index >= size || members[index] == NULL) {
        throw Exception("Index out of bounds");
    }
    return *members[index];
}
