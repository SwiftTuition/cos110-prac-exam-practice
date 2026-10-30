#ifndef MARKETING_H
#define MARKETING_H

#include "Department.h"

class Marketing : public Department {
   public:
    Marketing(int size);
    string getName();

   protected:
    float costToCompany();
};

#endif
