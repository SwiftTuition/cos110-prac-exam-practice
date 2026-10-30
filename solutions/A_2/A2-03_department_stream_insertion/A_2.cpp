#include "Department.h"

ostream& operator<<(ostream& out, Department& d) {
    // getName() and costToCompany() are virtual, so a Sales object prints as Sales.
    out << "Department: " << d.getName() << " (cost R" << d.costToCompany() << ")" << endl;
    bool anyTeam = false;
    for (int i = 0; i < d.size; i++) {
        if (d.teams[i] != NULL) {
            out << *d.teams[i];
            anyTeam = true;
        }
    }
    if (!anyTeam) {
        out << "  (no teams)" << endl;
    }
    return out;
}
