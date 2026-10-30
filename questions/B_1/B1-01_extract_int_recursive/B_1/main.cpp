#include <iostream>
#include <string>

#include "Employee.h"
#include "Exception.h"

using namespace std;

int main() {
    string id = "9702140123081";
    cout << "Year: " << Employee::extractIntFromString(id, 0, 2) << endl;
    cout << "Month: " << Employee::extractIntFromString(id, 2, 4) << endl;
    cout << "Day: " << Employee::extractIntFromString(id, 4, 6) << endl;
    cout << "Gender digits: " << Employee::extractIntFromString(id, 6, 10) << endl;
    cout << "Bad range: " << Employee::extractIntFromString("12345", 3, 2) << endl;
    cout << "Not a digit: " << Employee::extractIntFromString("12a45", 0, 5) << endl;

    Employee* sipho = new Employee("Sipho", "Dlamini", 34, 'M');
    sipho->setIDNum("9105225800087");
    cout << *sipho << endl;
    try {
        sipho->setIDNum("91052258X0087");
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    try {
        sipho->setIDNum("910522580008");
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    cout << *sipho << endl;
    delete sipho;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Year: 97
Month: 2
Day: 14
Gender digits: 123
Bad range: -1
Not a digit: -1
Sipho Dlamini, 34, M, ID: 9105225800087
Caught: ID number must only contain digits
Caught: ID number must have 13 digits
Sipho Dlamini, 34, M, ID: 9105225800087
*/
