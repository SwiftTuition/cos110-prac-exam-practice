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
    // Rule of three (all given): the copy constructor, operator= and the destructor
    // each handle the employees deeply.
    Team(const Team& other);
    Team& operator=(const Team& other);
    ~Team();
    void addMember(Employee* employee);
    void removeMember(int index);
    const Employee& operator[](int index);
    int getSize();
    int getMemberCount();

    // Returns a new team with copies of the members of this team, then of other.
    Team operator+(const Team& other) const;

    friend ostream& operator<<(ostream& out, const Team& t);
};

#endif
