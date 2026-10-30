#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

class Exception {
   public:
    string message;

    Exception(string message);
    string what();

    friend ostream& operator<<(ostream& out, const Exception& e);
};

#endif
