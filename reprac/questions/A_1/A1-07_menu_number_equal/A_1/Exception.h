#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

class Exception {
   private:
    string msg;

   public:
    Exception(string msg);
    virtual ~Exception();
    void printException();

    friend ostream& operator<<(ostream& out, const Exception& e);
};

class InvalidType : public Exception {
   public:
    InvalidType(string type);
};

class NothingMatchingFilter : public Exception {
   public:
    NothingMatchingFilter(string filter);
};

class NothingAboveMinimumValue : public NothingMatchingFilter {
   public:
    NothingAboveMinimumValue();
};

class NothingBelowMaximumValue : public NothingMatchingFilter {
   public:
    NothingBelowMaximumValue();
};

class NotFoundException : public Exception {
   public:
    NotFoundException();
};

class StarterNotFound : public NotFoundException {
   public:
    StarterNotFound();
};

class MainNotFound : public NotFoundException {
   public:
    MainNotFound();
};

class DessertNotFound : public NotFoundException {
   public:
    DessertNotFound();
};

#endif
