#include "Team.h"

void Team::addMember(Employee* employee) {
    if (employee == NULL) {
        throw Exception("Employee is NULL");
    }
    // Look at every slot first: the same pointer may sit after an empty slot.
    for (int i = 0; i < size; i++) {
        if (members[i] == employee) {
            throw Exception("Employee is already in the team");
        }
    }
    for (int i = 0; i < size; i++) {
        if (members[i] == NULL) {
            members[i] = employee;
            return;
        }
    }
    throw Exception("Team is full");
}
