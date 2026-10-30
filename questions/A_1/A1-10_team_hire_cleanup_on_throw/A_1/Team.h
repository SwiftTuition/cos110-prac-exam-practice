#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <string>

#include "Employee.h"
#include "Exception.h"

using namespace std;

class Team {
   private:
    Employee** members;
    int size;

   public:
    Team(int size);
    ~Team();
    void addMember(Employee* employee);
    const Employee& operator[](int index);
    int getSize();
    int getMemberCount();

    // Makes a new employee, sets its ID number and adds it to the team.
    // If anything throws, frees the new employee and throws the same exception again.
    void hire(string firstName, string surName, int age, char gender, string idNum);

    friend ostream& operator<<(ostream& out, const Team& t);

   private:
    // Not needed in this question; private so it cannot be used by mistake.
    Team(const Team& other);
    Team& operator=(const Team& other);
};

#endif
