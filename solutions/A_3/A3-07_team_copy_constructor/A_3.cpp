#include "Team.h"

Team::Team(const Team& other) : members(NULL), size(0) {
    // A new object has no array yet. members is NULL and size is 0,
    // so operator= has nothing old to delete before it makes the deep copy.
    *this = other;
}
