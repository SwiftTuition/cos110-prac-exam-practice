#ifndef HR_H
#define HR_H

#include "Department.h"

class HR : public Department {
   public:
    HR(int size);
    string getName();

   protected:
    float costToCompany();
};

#endif
