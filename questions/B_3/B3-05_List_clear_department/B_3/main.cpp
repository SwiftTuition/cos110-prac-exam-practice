#include <iostream>
#include <string>

#include "Company.h"
#include "Department.h"
#include "Development.h"
#include "Employee.h"
#include "HR.h"
#include "List.h"
#include "Marketing.h"
#include "Sales.h"
#include "Team.h"

using namespace std;

int main() {
    List<int> numbers;
    numbers.prepend(3);
    numbers.prepend(2);
    numbers.prepend(1);
    cout << numbers << endl;
    numbers.clear();
    cout << numbers << " (size " << numbers.getSize() << ")" << endl;

    Team* salesTeam = new Team(1);
    salesTeam->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    Department* sales = new Sales(1);
    sales->addTeam(salesTeam);

    Team* hrTeam = new Team(2);
    hrTeam->addMember(new Employee("Anna", "Botha", 41, 'F'));
    hrTeam->addMember(new Employee("Sipho", "Dlamini", 34, 'M'));
    Department* hr = new HR(1);
    hr->addTeam(hrTeam);

    Company yyra;
    yyra.addDepartment(sales);
    yyra.addDepartment(hr);
    cout << yyra;
    cout << "Total cost: R" << yyra.costToCompany() << endl;

    List<Department*> spare;
    spare.prepend(new Marketing(1));
    spare.prepend(new Development(2));
    cout << "Spare departments: " << spare.getSize() << endl;
    spare.clear();
    cout << "Spare departments after clear: " << spare.getSize() << endl;

    // yyra is destroyed here: ~List() calls clear(), which deletes Sales and HR.
    return 0;
}
/*
ExpectedOutput:
*/
/*
1->2->3
Empty List (size 0)
Company with 2 departments
HR (cost R24000)
Team:
  Anna Botha, 41, F, ID: none
  Sipho Dlamini, 34, M, ID: none
Sales (cost R15000)
Team:
  Thandi Mokoena, 29, F, ID: none
Total cost: R39000
Spare departments: 2
Spare departments after clear: 0
*/
