#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>

#include "Department.h"
#include "List.h"

using namespace std;

class Company {
   private:
    List<Department*> departments;

   public:
    Company();
    ~Company();
    void addDepartment(Department* department);
    List<Department*>& getDepartments();
    float costToCompany();
    // Returns the total cost of the department in curr and of every department after it.
    // A node that holds NULL adds 0. Write this function in B_1.cpp using recursion.
    float totalCost(Node<Department*>* curr);

    friend ostream& operator<<(ostream& out, Company& c);

   private:
    // Not needed in this question; private so it cannot be used by mistake.
    Company(const Company& other);
    Company& operator=(const Company& other);
};

#endif
