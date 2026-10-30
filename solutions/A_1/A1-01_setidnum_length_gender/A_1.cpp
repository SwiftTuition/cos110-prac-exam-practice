#include "Employee.h"

void Employee::setIDNum(string idNum) {
    if ((int)idNum.length() != 13) {
        throw Exception("ID number must have 13 digits");
    }
    // extractIntFromString throws "Not a digit" itself; that exception is not caught here.
    int genderDigits = extractIntFromString(idNum, 6, 10);
    char idGender = 'F';
    if (genderDigits >= 5000) {
        idGender = 'M';
    }
    if (idGender != gender) {
        throw Exception("ID number does not match gender");
    }
    this->idNum = idNum;
}
