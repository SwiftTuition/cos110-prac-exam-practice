#include "Employee.h"

void Employee::setIDNum(string idNum) {
    if ((int)idNum.length() != 13) {
        throw Exception("ID number must have 13 digits");
    }
    for (int i = 0; i < (int)idNum.length(); i++) {
        if (idNum[i] < '0' || idNum[i] > '9') {
            throw Exception("ID number must contain only digits");
        }
    }
    int month = extractIntFromString(idNum, 2, 4);
    if (month < 1 || month > 12) {
        throw Exception("Invalid birth month");
    }
    int day = extractIntFromString(idNum, 4, 6);
    if (day < 1 || day > 31) {
        throw Exception("Invalid birth day");
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
