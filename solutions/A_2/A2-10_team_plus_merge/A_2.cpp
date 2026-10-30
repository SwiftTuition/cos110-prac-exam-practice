#include "Team.h"

Team Team::operator+(const Team& other) const {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (members[i] != NULL) {
            count++;
        }
    }
    for (int i = 0; i < other.size; i++) {
        if (other.members[i] != NULL) {
            count++;
        }
    }

    Team result(count);
    int next = 0;
    for (int i = 0; i < size; i++) {
        if (members[i] != NULL) {
            result.members[next] = new Employee(*members[i]);
            next++;
        }
    }
    for (int i = 0; i < other.size; i++) {
        if (other.members[i] != NULL) {
            result.members[next] = new Employee(*other.members[i]);
            next++;
        }
    }
    return result;
}
