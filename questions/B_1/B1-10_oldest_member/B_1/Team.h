#ifndef TEAM_H
#define TEAM_H

#include <iostream>

#include "Employee.h"
#include "Exception.h"

using namespace std;

// size is the number of slots in members. Every slot starts as NULL.
// An empty slot is NULL. The team owns (and deletes) its employees.
class Team {
   private:
    Employee** members;
    int size;

   public:
    Team(int size);
    ~Team();
    void addMember(Employee* employee);
    void removeMember(int index);
    const Employee& operator[](int index);
    int getSize();
    // Returns the age of the oldest employee from index to the end of members.
    // Write this function in B_1.cpp using recursion.
    int oldest(int index);

    friend ostream& operator<<(ostream& out, const Team& t);

   private:
    // Not needed in this question; private so it cannot be used by mistake.
    Team(const Team& other);
    Team& operator=(const Team& other);
};

#endif
