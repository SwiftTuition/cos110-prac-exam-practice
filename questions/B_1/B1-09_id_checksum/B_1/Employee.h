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
    static int extractIntFromString(string str, int start, int end);
    // Returns the Luhn sum of the digits from index to the end of id.
    // id holds digits only. Returns 0 if index is out of range.
    // Write this function in B_1.cpp using recursion.
    static int checksum(string id, int index);

    friend ostream& operator<<(ostream& out, const Employee& e);
};

#endif
