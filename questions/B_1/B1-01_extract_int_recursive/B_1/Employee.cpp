#include "Employee.h"

Employee::Employee(string firstName, string surName, int age, char gender)
    : age(age), firstName(firstName), surName(surName), idNum(""), gender(gender) {
}

Employee::Employee(const Employee& other)
    : age(other.age), firstName(other.firstName), surName(other.surName), idNum(other.idNum), gender(other.gender) {
}

string Employee::getFirstName() {
    return firstName;
}

string Employee::getSurName() {
    return surName;
}

string Employee::getIDNum() {
    return idNum;
}

int Employee::getAge() {
    return age;
}

char Employee::getGender() {
    return gender;
}

// Every part of the ID is read with extractIntFromString.
// A result of -1 means the part was not made of digits only.
void Employee::setIDNum(string idNum) {
    if (idNum.length() != 13) {
        throw Exception("ID number must have 13 digits");
    }
    if (extractIntFromString(idNum, 0, 6) == -1 || extractIntFromString(idNum, 6, 10) == -1 ||
        extractIntFromString(idNum, 10, 13) == -1) {
        throw Exception("ID number must only contain digits");
    }
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

ostream& operator<<(ostream& out, const Employee& e) {
    out << e.firstName << " " << e.surName << ", " << e.age << ", " << e.gender << ", ID: ";
    if (e.idNum == "") {
        out << "none";
    } else {
        out << e.idNum;
    }
    return out;
}
