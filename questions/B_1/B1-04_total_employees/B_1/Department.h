#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <iostream>
#include <string>

#include "Exception.h"
#include "Team.h"

using namespace std;

// size is the number of slots in teams. Every slot starts as NULL.
// An empty slot is NULL. The department owns (and deletes) its teams.
class Department {
   private:
    Team** teams;
    int size;

   public:
    Department(int size);
    virtual ~Department();
    void addTeam(Team* team);
    Team*& operator[](int index);
    int getSize();
    virtual float costToCompany();
    virtual string getName();
    // Adds up the members of every team from index to the end of teams.
    // Write this function in B_1.cpp using recursion.
    int totalEmployees(int index);

    friend ostream& operator<<(ostream& out, Department& d);

   private:
    // Not needed in this question; private so it cannot be used by mistake.
    Department(const Department& other);
    Department& operator=(const Department& other);
};

#endif
