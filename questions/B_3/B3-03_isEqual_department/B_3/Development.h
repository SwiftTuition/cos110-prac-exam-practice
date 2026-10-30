#ifndef DEVELOPMENT_H
#define DEVELOPMENT_H

#include "Department.h"

class Development : public Department {
   public:
    Development(int size);
    string getName();

   protected:
    float costToCompany();
};

#endif
