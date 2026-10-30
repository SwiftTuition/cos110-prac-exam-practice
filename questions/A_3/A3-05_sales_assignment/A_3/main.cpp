#include <iostream>
#include <string>

#include "Department.h"
#include "Employee.h"
#include "Exception.h"
#include "Sales.h"
#include "Team.h"

using namespace std;

void show(string label, Sales& s) {
    Department& d = s;
    cout << label << endl << d;
    cout << "Target: " << s.getTarget() << ", cost: R" << d.costToCompany() << endl;
}

int main() {
    Sales* a = new Sales(1);
    a->setTarget(100);
    Team* t1 = new Team(1);
    t1->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    a->addTeam(t1);

    Sales* b = new Sales(2);
    b->setTarget(250);
    Team* t2 = new Team(2);
    t2->addMember(new Employee("Sipho", "Dlamini", 34, 'M'));
    t2->addMember(new Employee("Anna", "Botha", 41, 'F'));
    b->addTeam(t2);

    show("Sales a before:", *a);
    show("Sales b:", *b);

    *a = *b;
    show("Sales a after *a = *b:", *a);

    (*b)[0]->removeMember(0);
    b->setTarget(300);
    show("Sales b after the changes:", *b);
    show("Sales a has not changed:", *a);

    delete a;
    delete b;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Sales a before:
Sales of size 1:
Slot 0: Team of size 1:
  0: Thandi Mokoena, 29, F, ID: none
Target: 100, cost: R15000
Sales b:
Sales of size 2:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Target: 250, cost: R30000
Sales a after *a = *b:
Sales of size 2:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Target: 250, cost: R30000
Sales b after the changes:
Sales of size 2:
Slot 0: Team of size 2:
  0: empty
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Target: 300, cost: R15000
Sales a has not changed:
Sales of size 2:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Target: 250, cost: R30000
*/
