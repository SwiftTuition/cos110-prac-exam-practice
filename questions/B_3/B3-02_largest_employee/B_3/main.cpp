#include <iostream>
#include <string>

#include "Employee.h"
#include "Templates.h"

using namespace std;

int main() {
    cout << largest(3, 7) << endl;
    cout << largest(2.5, 1.5) << endl;
    cout << largest(string("apple"), string("pear")) << endl;

    Employee thandi("Thandi", "Mokoena", 29, 'F');
    Employee sipho("Sipho", "Dlamini", 34, 'M');
    cout << largest(thandi, sipho) << endl;
    cout << largest(sipho, thandi) << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
7
2.5
pear
Sipho Dlamini, 34, M, ID: none
Sipho Dlamini, 34, M, ID: none
*/
