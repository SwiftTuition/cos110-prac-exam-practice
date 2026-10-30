#include "Department.h"

Department::Department(int size) : size(size) {
    teams = new Team*[size];
    for (int i = 0; i < size; i++) {
        teams[i] = NULL;
    }
}

Department::~Department() {
    for (int i = 0; i < size; i++) {
        delete teams[i];
    }
    delete[] teams;
}

// The department owns the teams added to it.
void Department::addTeam(Team* team) {
    for (int i = 0; i < size; i++) {
        if (teams[i] == NULL) {
            teams[i] = team;
            return;
        }
    }
    throw Exception("Department is full");
}

Team*& Department::operator[](int index) {
    if (index < 0 || index >= size) {
        throw Exception("Index out of bounds");
    }
    return teams[index];
}

int Department::getSize() {
    return size;
}

float Department::costToCompany() {
    return 0;
}

string Department::getName() {
    return "Department";
}

ostream& operator<<(ostream& out, Department& d) {
    out << d.getName() << " of size " << d.size << ":" << endl;
    for (int i = 0; i < d.size; i++) {
        out << "Slot " << i << ": ";
        if (d.teams[i] == NULL) {
            out << "empty" << endl;
        } else {
            out << *d.teams[i];
        }
    }
    return out;
}
