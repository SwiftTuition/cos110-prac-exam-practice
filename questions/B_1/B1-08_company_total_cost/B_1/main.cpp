#include <iostream>

#include "Company.h"
#include "Department.h"
#include "Development.h"
#include "Employee.h"
#include "Exception.h"
#include "HR.h"
#include "List.h"
#include "Marketing.h"
#include "Sales.h"
#include "Team.h"

using namespace std;

int main() {
    Team* t1 = new Team(2);
    t1->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    t1->addMember(new Employee("Sipho", "Dlamini", 34, 'M'));
    Team* t2 = new Team(3);
    t2->addMember(new Employee("Anna", "Botha", 41, 'F'));
    Team* t3 = new Team(1);
    t3->addMember(new Employee("Ravi", "Naidoo", 38, 'M'));
    Team* t4 = new Team(1);
    t4->addMember(new Employee("Lebo", "Nkosi", 25, 'F'));

    Department* dev = new Development(1);
    dev->addTeam(t1);
    Department* sales = new Sales(2);
    sales->addTeam(t2);
    sales->addTeam(t3);
    Department* hr = new HR(1);
    hr->addTeam(t4);

    Company yyra;
    yyra.addDepartment(dev);
    yyra.addDepartment(sales);
    yyra.addDepartment(hr);
    cout << yyra;

    cout << "Total cost: R" << yyra.costToCompany() << endl;
    Node<Department*>* first = yyra.getDepartments().head();
    cout << "Cost from the second department: R" << yyra.totalCost(first->next()) << endl;
    cout << "Cost from the third department: R" << yyra.totalCost(first->next()->next()) << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Company with 3 departments
HR of size 1:
Slot 0: Team of size 1:
  0: Lebo Nkosi, 25, F, ID: none
Sales of size 2:
Slot 0: Team of size 3:
  0: Anna Botha, 41, F, ID: none
  1: empty
  2: empty
Slot 1: Team of size 1:
  0: Ravi Naidoo, 38, M, ID: none
Development of size 1:
Slot 0: Team of size 2:
  0: Thandi Mokoena, 29, F, ID: none
  1: Sipho Dlamini, 34, M, ID: none
Total cost: R92000
Cost from the second department: R80000
Cost from the third department: R50000
*/
