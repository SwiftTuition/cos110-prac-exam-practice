#include <iostream>
#include <string>

#include "Department.h"
#include "Development.h"
#include "Employee.h"
#include "HR.h"
#include "List.h"
#include "Sales.h"
#include "Team.h"

using namespace std;

int main() {
    List<int> numbers;
    numbers.prepend(30);
    numbers.prepend(20);
    numbers.prepend(10);
    numbers.printAll();

    Team* salesTeam = new Team(1);
    salesTeam->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    Department* sales = new Sales(1);
    sales->addTeam(salesTeam);

    Team* hrTeam = new Team(2);
    hrTeam->addMember(new Employee("Anna", "Botha", 41, 'F'));
    hrTeam->addMember(new Employee("Sipho", "Dlamini", 34, 'M'));
    Department* hr = new HR(1);
    hr->addTeam(hrTeam);

    List<Department*> departments;
    departments.prepend(sales);
    departments.prepend(hr);
    departments.printAll();

    // This list does not own the Departments, so main deletes them.
    delete hr;
    delete sales;
    return 0;
}
/*
ExpectedOutput:
*/
/*
0: 10
1: 20
2: 30
0: HR (cost R24000)
Team:
  Anna Botha, 41, F, ID: none
  Sipho Dlamini, 34, M, ID: none
1: Sales (cost R15000)
Team:
  Thandi Mokoena, 29, F, ID: none
*/
