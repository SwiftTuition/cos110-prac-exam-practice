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
    // This version checks the length, the digits, the month, the day and the gender.
    // See QUESTION.md for the order of the checks and the messages.
    void setIDNum(string idNum);
    static int extractIntFromString(string str, int start, int end);

    friend ostream& operator<<(ostream& out, const Employee& e);
};

#endif
