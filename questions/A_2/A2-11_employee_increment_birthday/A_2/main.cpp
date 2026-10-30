
#include <iostream>

#include "Employee.h"

using namespace std;

int main() {
    Employee* thandi = new Employee("Thandi", "Mokoena", 29, 'F');

    ++(*thandi);
    cout << *thandi << endl;

    Employee before = (*thandi)++;
    cout << "Before: " << before << endl;
    cout << "After: " << *thandi << endl;

    delete thandi;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Thandi Mokoena, 30, F, ID: none
Before: Thandi Mokoena, 30, F, ID: none
After: Thandi Mokoena, 31, F, ID: none
*/
