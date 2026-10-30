#include <iostream>
#include <string>

#include "Company.h"
#include "Department.h"
#include "Development.h"
#include "Employee.h"
#include "HR.h"
#include "Sales.h"
#include "Team.h"

using namespace std;

void tryRemove(Company& company, string name) {
    bool removed = company.removeDepartment(name);
    cout << "removeDepartment(" << name << "): " << (removed ? "true" : "false") << endl;
}

int main() {
    Team* salesTeam = new Team(2);
    salesTeam->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    Department* sales = new Sales(1);
    sales->addTeam(salesTeam);

    Team* hrTeam = new Team(2);
    hrTeam->addMember(new Employee("Anna", "Botha", 41, 'F'));
    hrTeam->addMember(new Employee("Sipho", "Dlamini", 34, 'M'));
    Department* hr = new HR(1);
    hr->addTeam(hrTeam);

    Team* devTeam = new Team(1);
    devTeam->addMember(new Employee("Lebo", "Nkosi", 25, 'F'));
    Department* dev = new Development(1);
    dev->addTeam(devTeam);

    Company yyra;
    yyra.addDepartment(sales);
    yyra.addDepartment(hr);
    yyra.addDepartment(dev);
    cout << yyra;
    cout << "Total cost: R" << yyra.costToCompany() << endl;

    tryRemove(yyra, "HR");
    tryRemove(yyra, "Finance");
    cout << yyra;
    cout << "Total cost: R" << yyra.costToCompany() << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Company with 3 departments
Development (cost R25000)
Team:
  Lebo Nkosi, 25, F, ID: none
HR (cost R24000)
Team:
  Anna Botha, 41, F, ID: none
  Sipho Dlamini, 34, M, ID: none
Sales (cost R15000)
Team:
  Thandi Mokoena, 29, F, ID: none
Total cost: R64000
removeDepartment(HR): true
removeDepartment(Finance): false
Company with 2 departments
Development (cost R25000)
Team:
  Lebo Nkosi, 25, F, ID: none
Sales (cost R15000)
Team:
  Thandi Mokoena, 29, F, ID: none
Total cost: R40000
*/
