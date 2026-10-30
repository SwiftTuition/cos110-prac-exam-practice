#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>

#include "Department.h"
#include "List.h"

using namespace std;

// As in the UML, Company has no destructor. The departments are deleted by
// List<Department*>::clear(), which ~List() calls when the company is destroyed.
class Company {
   private:
    List<Department*> departments;

   public:
    Company();
    void addDepartment(Department* department);
    float costToCompany();

    friend ostream& operator<<(ostream& out, Company& c);
};

#endif
