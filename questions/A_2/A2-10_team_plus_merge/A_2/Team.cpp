#include "Team.h"

Team::Team(int size) : size(size) {
    members = new Employee*[size];
    for (int i = 0; i < size; i++) {
        members[i] = NULL;
    }
}

// Deep copy: every employee is copied. Empty (NULL) slots stay NULL.
Team::Team(const Team& other) : size(other.size) {
    members = new Employee*[size];
    for (int i = 0; i < size; i++) {
        if (other.members[i] != NULL) {
            members[i] = new Employee(*other.members[i]);
        } else {
            members[i] = NULL;
        }
    }
}

// Deep copy assignment. Empty (NULL) slots stay NULL.
Team& Team::operator=(const Team& other) {
    if (this == &other) {
        return *this;
    }
    for (int i = 0; i < size; i++) {
        delete members[i];
    }
    delete[] members;
    size = other.size;
    members = new Employee*[size];
    for (int i = 0; i < size; i++) {
        if (other.members[i] != NULL) {
            members[i] = new Employee(*other.members[i]);
        } else {
            members[i] = NULL;
        }
    }
    return *this;
}

Team::~Team() {
    for (int i = 0; i < size; i++) {
        delete members[i];
    }
    delete[] members;
}

// Puts the employee in the first empty (NULL) slot. The team owns the employees added to it.
void Team::addMember(Employee* employee) {
    for (int i = 0; i < size; i++) {
        if (members[i] == NULL) {
            members[i] = employee;
            return;
        }
    }
    throw Exception("Team is full");
}

// Deletes the employee at index and makes the slot empty (NULL).
// Does nothing if the index is out of range or the slot is already empty.
void Team::removeMember(int index) {
    if (index < 0 || index >= size || members[index] == NULL) {
        return;
    }
    delete members[index];
    members[index] = NULL;
}

const Employee& Team::operator[](int index) {
    if (index < 0 || index >= size || members[index] == NULL) {
        throw Exception("Index out of bounds");
    }
    return *members[index];
}

int Team::getSize() {
    return size;
}

// Counts the slots that are not empty (not NULL).
int Team::getMemberCount() {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (members[i] != NULL) {
            count++;
        }
    }
    return count;
}

ostream& operator<<(ostream& out, const Team& t) {
    int count = 0;
    for (int i = 0; i < t.size; i++) {
        if (t.members[i] != NULL) {
            count++;
        }
    }
    out << "Team (" << count << "/" << t.size << "):" << endl;
    if (count == 0) {
        out << "  (no members)" << endl;
    }
    for (int i = 0; i < t.size; i++) {
        if (t.members[i] != NULL) {
            out << "  " << *t.members[i] << endl;
        }
    }
    return out;
}
