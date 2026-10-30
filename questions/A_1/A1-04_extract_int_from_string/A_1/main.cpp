
#include <iostream>

#include "Employee.h"
#include "Exception.h"

using namespace std;

void tryExtract(string str, int start, int end) {
    try {
        int value = Employee::extractIntFromString(str, start, end);
        cout << "\"" << str << "\" [" << start << ", " << end << ") = " << value << endl;
    } catch (Exception& e) {
        cout << "\"" << str << "\" [" << start << ", " << end << "): " << e.what() << endl;
    }
}

int main() {
    tryExtract("9702140123081", 0, 2);
    tryExtract("9702140123081", 2, 4);
    tryExtract("9702140123081", 6, 10);
    tryExtract("12a4", 0, 4);
    tryExtract("1234", 2, 2);

    Employee* thandi = new Employee("Thandi", "Mokoena", 29, 'F');
    Employee* sipho = new Employee("Sipho", "Dlamini", 35, 'M');
    try {
        thandi->setIDNum("9702140123081");
        sipho->setIDNum("9105225800087");
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
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
"9702140123081" [0, 2) = 97
"9702140123081" [2, 4) = 2
"9702140123081" [6, 10) = 123
"12a4" [0, 4): Not a digit
"1234" [2, 2): Invalid range
Thandi Mokoena, 29, F, ID: 9702140123081
Sipho Dlamini, 35, M, ID: 9105225800087
*/
