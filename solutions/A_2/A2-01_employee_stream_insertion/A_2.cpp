#include "Employee.h"

ostream& operator<<(ostream& out, const Employee& e) {
    // e is const and the getters are not const, so a friend reads the members directly.
    out << e.firstName << " " << e.surName << ", " << e.age << ", " << e.gender << ", ID: ";
    if (e.idNum == "") {
        out << "none";
    } else {
        out << e.idNum;
    }
    return out;
}
