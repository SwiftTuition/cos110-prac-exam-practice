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

// Reads the digits from index start up to, but not including, index end.
int Employee::extractIntFromString(string str, int start, int end) {
    if (start < 0 || start >= end || end > (int)str.length()) {
        throw Exception("Invalid range");
    }
    int result = 0;
    for (int i = start; i < end; i++) {
        if (str[i] < '0' || str[i] > '9') {
            throw Exception("Not a digit");
        }
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

void Employee::setIDNum(string idNum) {
    if (idNum.length() != 13) {
        throw Exception("ID number must have 13 digits");
    }
    if (!isAllDigits(idNum, 0)) {
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
