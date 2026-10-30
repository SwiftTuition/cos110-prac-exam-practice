#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <string>

#include "Department.h"
#include "List.h"

using namespace std;

class Company {
   private:
    List<Department*> departments;

    // Not needed in this question; private so it cannot be used by mistake.
    Company(const Company& other);
    Company& operator=(const Company& other);

   public:
    Company();
    ~Company();
    void addDepartment(Department* department);
    float costToCompany();
    bool removeDepartment(string name);

    friend ostream& operator<<(ostream& out, Company& c);
};

#endif
