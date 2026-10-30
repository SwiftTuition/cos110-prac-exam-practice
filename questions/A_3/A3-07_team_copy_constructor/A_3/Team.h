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
    // Write this function in A_3.cpp.
    Team(const Team& other);
    ~Team();
    Team& operator=(const Team& other);
    void addMember(Employee* employee);
    void removeMember(int index);
    const Employee& operator[](int index);
    int getSize();
    int getMemberCount();

    friend ostream& operator<<(ostream& out, const Team& t);
};

#endif
