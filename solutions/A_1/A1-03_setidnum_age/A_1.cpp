#include "Employee.h"

void Employee::setIDNum(string idNum) {
    if ((int)idNum.length() != 13) {
        throw Exception("ID number must have 13 digits");
    }
    int yy = extractIntFromString(idNum, 0, 2);
    int birthYear = 1900 + yy;
    if (yy <= 26) {
        birthYear = 2000 + yy;
    }
    if (age != 2026 - birthYear) {
        throw Exception("ID number does not match age");
    }
    char idGender = 'F';
    if (extractIntFromString(idNum, 6, 10) >= 5000) {
        idGender = 'M';
    }
    if (idGender != gender) {
        throw Exception("ID number does not match gender");
    }
    this->idNum = idNum;
}
