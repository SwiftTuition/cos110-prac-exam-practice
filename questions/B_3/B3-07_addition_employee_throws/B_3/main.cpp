#include <iostream>
#include <string>

#include "Employee.h"
#include "Exception.h"
#include "Templates.h"

using namespace std;

int main() {
    cout << addition(3, 4.5) << endl;
    cout << addition(2.5, 3) << endl;
    cout << addition(string("Human "), string("Resources")) << endl;

    Employee thandi("Thandi", "Mokoena", 29, 'F');
    Employee sipho("Sipho", "Dlamini", 34, 'M');
    try {
        Employee both = addition(thandi, sipho);
        cout << both << endl;
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    cout << "Program continues" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
7
5.5
Human Resources
Caught: Cannot add two employees
Program continues
*/
