#include <iostream>
#include <string>

#include "Employee.h"
#include "Exception.h"

using namespace std;

int main() {
    string good = "9702140123086";
    int sum = Employee::checksum(good, 0);
    cout << "Luhn sum of " << good << ": " << sum << endl;
    cout << "Valid: " << (sum % 10 == 0 ? "yes" : "no") << endl;

    string bad = "9702140123081";
    sum = Employee::checksum(bad, 0);
    cout << "Luhn sum of " << bad << ": " << sum << endl;
    cout << "Valid: " << (sum % 10 == 0 ? "yes" : "no") << endl;

    cout << "Sum from index 6 of " << good << ": " << Employee::checksum(good, 6) << endl;

    Employee* thandi = new Employee("Thandi", "Mokoena", 29, 'F');
    try {
        thandi->setIDNum(bad);
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    thandi->setIDNum(good);
    cout << *thandi << endl;
    delete thandi;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Luhn sum of 9702140123086: 50
Valid: yes
Luhn sum of 9702140123081: 45
Valid: no
Sum from index 6 of 9702140123086: 23
Caught: ID number has a wrong check digit
Thandi Mokoena, 29, F, ID: 9702140123086
*/
