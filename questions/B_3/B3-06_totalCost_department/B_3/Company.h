#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>

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

    friend ostream& operator<<(ostream& out, Company& c);
};

#endif
