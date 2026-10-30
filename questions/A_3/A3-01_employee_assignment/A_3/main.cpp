#include <iostream>

#include "Employee.h"
#include "Exception.h"

using namespace std;

int main() {
    Employee* thandi = new Employee("Thandi", "Mokoena", 29, 'F');
    Employee* sipho = new Employee("Sipho", "Dlamini", 34, 'M');
    thandi->setIDNum("9702140123081");
    sipho->setIDNum("9105225800087");

    cout << "Before:" << endl;
    cout << *thandi << endl;
    cout << *sipho << endl;

    *thandi = *sipho;

    cout << "After *thandi = *sipho:" << endl;
    cout << *thandi << endl;
    cout << *sipho << endl;

    delete thandi;
    delete sipho;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Before:
Thandi Mokoena, 29, F, ID: 9702140123081
Sipho Dlamini, 34, M, ID: 9105225800087
After *thandi = *sipho:
Sipho Dlamini, 34, M, ID: 9105225800087
Sipho Dlamini, 34, M, ID: 9105225800087
*/
