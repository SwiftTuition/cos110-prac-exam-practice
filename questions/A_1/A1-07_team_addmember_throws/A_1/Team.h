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
    // Throws Exception("Employee is NULL"), Exception("Employee is already in the team")
    // or Exception("Team is full"). After a throw, the caller still owns employee.
    void addMember(Employee* employee);
    void removeMember(int index);
    const Employee& operator[](int index);
    int getSize();
    int getMemberCount();

    friend ostream& operator<<(ostream& out, const Team& t);

   private:
    // Not needed in this question; private so it cannot be used by mistake.
    Team(const Team& other);
    Team& operator=(const Team& other);
};

#endif
