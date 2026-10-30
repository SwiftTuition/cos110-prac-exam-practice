
#include <iostream>

#include "Employee.h"
#include "Exception.h"

using namespace std;

int main() {
    Employee* thandi = new Employee("Thandi", "Mokoena", 29, 'F');
    Employee* sipho = new Employee("Sipho", "Dlamini", 35, 'M');

    thandi->setIDNum("9702140123081");
    cout << *thandi << endl;

    try {
        sipho->setIDNum("910522580008");
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    try {
        sipho->setIDNum("9105220800087");
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    cout << *sipho << endl;

    sipho->setIDNum("9105225800087");
    cout << *sipho << endl;

    delete thandi;
    delete sipho;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Thandi Mokoena, 29, F, ID: 9702140123081
Caught: ID number must have 13 digits
Caught: ID number does not match gender
Sipho Dlamini, 35, M, ID: none
Sipho Dlamini, 35, M, ID: 9105225800087
*/
