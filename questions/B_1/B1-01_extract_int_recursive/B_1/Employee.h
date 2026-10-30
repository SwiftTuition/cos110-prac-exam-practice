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
    // Reads the digits from index start up to, but not including, index end.
    // Returns -1 if the range is invalid or a character in the range is not a digit.
    // Write this function in B_1.cpp using recursion.
    static int extractIntFromString(string str, int start, int end);

    friend ostream& operator<<(ostream& out, const Employee& e);
};

#endif
