#include "Team.h"

const Employee& Team::operator[](int index) {
    // Check the range first, so that members[index] is never read outside the array.
    if (index < 0 || index >= size) {
        throw Exception("Index out of bounds");
    }
    if (members[index] == NULL) {
        throw Exception("No employee at this index");
    }
    return *members[index];
}
