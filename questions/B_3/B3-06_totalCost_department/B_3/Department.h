#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <iostream>
#include <string>

#include "Exception.h"
#include "Team.h"

using namespace std;

class Department {
   private:
    Team** teams;
    int size;

    // Not needed in this question; private so it cannot be used by mistake.
    Department(const Department& other);
    Department& operator=(const Department& other);

   protected:
    int countEmployees();

   public:
    Department(int size);
    virtual ~Department();
    void addTeam(Team* team);
    Team*& operator[](int index);
    int getSize();
    virtual float costToCompany();
    virtual string getName();

    friend ostream& operator<<(ostream& out, Department& d);
};

#endif
