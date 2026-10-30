#include <iostream>
#include <string>

#include "Department.h"
#include "Development.h"
#include "Employee.h"
#include "HR.h"
#include "Sales.h"
#include "Team.h"
#include "Templates.h"

using namespace std;

int main() {
    printItem(42);
    printItem(3.5);
    printItem(string("Yyra HRMS"));

    Team* team = new Team(2);
    team->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    Department* sales = new Sales(1);
    sales->addTeam(team);
    printItem(sales);

    Department* none = NULL;
    printItem(none);

    delete sales;
    return 0;
}
/*
ExpectedOutput:
*/
/*
42
3.5
Yyra HRMS
Sales (cost R15000)
Team:
  Thandi Mokoena, 29, F, ID: none
No department
*/
