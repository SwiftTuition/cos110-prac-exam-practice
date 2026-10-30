#ifndef SALES_H
#define SALES_H

#include "Department.h"

class Sales : public Department {
   private:
    int target;

   public:
    Sales(int size);
    // Write this function in A_3.cpp.
    Sales& operator=(const Sales& other);
    void setTarget(int target);
    int getTarget();
    string getName();

   protected:
    float costToCompany();
};

#endif
