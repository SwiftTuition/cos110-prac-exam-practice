
#include <iostream>

#include "Employee.h"

using namespace std;

int main() {
    Employee* thandi = new Employee("Thandi", "Mokoena", 29, 'F');
    Employee* sipho = new Employee("Sipho", "Dlamini", 35, 'M');
    thandi->setIDNum("9702140123081");

    cout << *thandi << endl;
    cout << *sipho << endl;
    cout << *thandi << " | " << *sipho << endl;

    delete thandi;
    delete sipho;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Thandi Mokoena, 29, F, ID: 9702140123081
Sipho Dlamini, 35, M, ID: none
Thandi Mokoena, 29, F, ID: 9702140123081 | Sipho Dlamini, 35, M, ID: none
*/
