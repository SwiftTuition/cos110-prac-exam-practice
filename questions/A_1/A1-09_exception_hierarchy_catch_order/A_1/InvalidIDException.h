#ifndef INVALIDIDEXCEPTION_H
#define INVALIDIDEXCEPTION_H

#include <string>

#include "Exception.h"

using namespace std;

// Thrown by setIDNum when an ID number has the wrong form (length or characters).
class InvalidIDException : public Exception {
   private:
    string badID;

   public:
    InvalidIDException(string badID, string message);
    string getBadID();
};

#endif
