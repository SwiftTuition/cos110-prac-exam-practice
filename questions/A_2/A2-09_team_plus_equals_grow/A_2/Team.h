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

    // Grows the array by one slot and puts a copy of *employee in the new last slot.
    // The caller still owns employee. A NULL employee changes nothing.
    Team& operator+=(Employee* employee);

    friend ostream& operator<<(ostream& out, const Team& t);

   private:
    // Not needed in this question; private so it cannot be used by mistake.
    Team(const Team& other);
    Team& operator=(const Team& other);
};

#endif
