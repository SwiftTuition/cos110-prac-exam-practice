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
    void removeMember(int index);
    // In this question operator[] is a const member function, so a const Team can use it.
    // Throws Exception("Index out of bounds") for a bad index or an empty slot.
    const Employee& operator[](int index) const;
    int getSize();
    int getMemberCount();

    friend ostream& operator<<(ostream& out, const Team& t);

   private:
    // Not needed in this question; private so it cannot be used by mistake.
    Team(const Team& other);
    Team& operator=(const Team& other);
};

#endif
