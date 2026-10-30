#include "Team.h"

int Team::operator()(string surName) const {
    for (int i = 0; i < size; i++) {
        if (members[i] != NULL && members[i]->getSurName() == surName) {
            return i;
        }
    }
    return -1;
}
