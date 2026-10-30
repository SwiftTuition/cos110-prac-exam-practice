#ifndef SALES_H
#define SALES_H

#include "Department.h"

class Sales : public Department {
   public:
    Sales(int size);
    string getName();

   protected:
    float costToCompany();
};

#endif
