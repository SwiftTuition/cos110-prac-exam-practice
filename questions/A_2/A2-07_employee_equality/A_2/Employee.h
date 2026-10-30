#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

#include "Exception.h"

using namespace std;

class Employee {
   private:
    int age;
    string firstName;
    string surName;
    string idNum;
    char gender;

   public:
    Employee(string firstName, string surName, int age, char gender);
    Employee(const Employee& other);
    string getFirstName();
    string getSurName();
    string getIDNum();
    int getAge();
    char getGender();
    void setIDNum(string idNum);
    static int extractIntFromString(string str, int start, int end);

    // Equal when the idNum strings are equal (two employees with no ID set are equal).
    bool operator==(const Employee& other) const;
    bool operator!=(const Employee& other) const;

    friend ostream& operator<<(ostream& out, const Employee& e);
};

#endif
