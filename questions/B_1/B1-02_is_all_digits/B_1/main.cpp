#include <iostream>
#include <string>

#include "Employee.h"
#include "Exception.h"

using namespace std;

int main() {
    cout << boolalpha;
    cout << "9702140123081 from 0: " << Employee::isAllDigits("9702140123081", 0) << endl;
    cout << "97021401230X1 from 0: " << Employee::isAllDigits("97021401230X1", 0) << endl;
    cout << "abc123 from 3: " << Employee::isAllDigits("abc123", 3) << endl;
    cout << "abc123 from 0: " << Employee::isAllDigits("abc123", 0) << endl;

    Employee* thandi = new Employee("Thandi", "Mokoena", 29, 'F');
    try {
        thandi->setIDNum("97021401230X1");
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    thandi->setIDNum("9702140123081");
    cout << *thandi << endl;
    delete thandi;
    return 0;
}
/*
ExpectedOutput:
*/
/*
9702140123081 from 0: true
97021401230X1 from 0: false
abc123 from 3: true
abc123 from 0: false
Caught: ID number must only contain digits
Thandi Mokoena, 29, F, ID: 9702140123081
*/
