#include "Team.h"

Team::Team(int size) : size(size) {
    members = new Employee*[size];
    for (int i = 0; i < size; i++) {
        members[i] = NULL;
    }
}

Team::~Team() {
    for (int i = 0; i < size; i++) {
        delete members[i];
    }
    delete[] members;
}

// Deep copy: every employee is copied. Empty slots stay empty (NULL).
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
        if (other.members[i] == NULL) {
            members[i] = NULL;
        } else {
            members[i] = new Employee(*other.members[i]);
        }
    }
    return *this;
}

// The team owns the employees added to it.
void Team::addMember(Employee* employee) {
    for (int i = 0; i < size; i++) {
        if (members[i] == NULL) {
            members[i] = employee;
            return;
        }
    }
    throw Exception("Team is full");
}

// Deletes the employee in this slot and makes the slot empty (NULL).
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
    out << "Team of size " << t.size << ":" << endl;
    for (int i = 0; i < t.size; i++) {
        out << "  " << i << ": ";
        if (t.members[i] == NULL) {
            out << "empty";
        } else {
            out << *t.members[i];
        }
        out << endl;
    }
    return out;
}
