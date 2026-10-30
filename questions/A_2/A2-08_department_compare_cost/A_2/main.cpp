
#include <iostream>
#include <string>

#include "Department.h"
#include "Development.h"
#include "Employee.h"
#include "HR.h"
#include "Marketing.h"
#include "Sales.h"
#include "Team.h"

using namespace std;

// Makes a team of count employees.
Team* makeTeam(int count) {
    string names[6] = {"Thandi", "Sipho", "Anna", "Lebo", "Pieter", "Kagiso"};
    Team* team = new Team(count);
    for (int i = 0; i < count; i++) {
        team->addMember(new Employee(names[i], "Worker", 30, 'F'));
    }
    return team;
}

void compare(Department& x, Department& y) {
    cout << x.getName() << " < " << y.getName() << ": " << (x < y ? "true" : "false") << endl;
    cout << x.getName() << " > " << y.getName() << ": " << (x > y ? "true" : "false") << endl;
}

int main() {
    Department* sales = new Sales(1);
    sales->addTeam(makeTeam(2));
    Department* dev = new Development(1);
    dev->addTeam(makeTeam(1));
    Department* hr = new HR(1);
    hr->addTeam(makeTeam(0));

    cout << sales->getName() << " costs R" << sales->costToCompany() << endl;
    cout << dev->getName() << " costs R" << dev->costToCompany() << endl;
    cout << hr->getName() << " costs R" << hr->costToCompany() << endl;
    compare(*sales, *dev);
    compare(*dev, *sales);
    compare(*hr, *dev);

    delete sales;
    delete dev;
    delete hr;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Sales costs R30000
Development costs R25000
HR costs R0
Sales < Development: false
Sales > Development: true
Development < Sales: true
Development > Sales: false
HR < Development: true
HR > Development: false
*/
