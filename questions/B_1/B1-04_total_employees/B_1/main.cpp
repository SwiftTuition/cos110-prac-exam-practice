#include <iostream>

#include "Department.h"
#include "Employee.h"
#include "Exception.h"
#include "Team.h"

using namespace std;

int main() {
    Department* d = new Department(4);
    Team* t1 = new Team(3);
    t1->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    t1->addMember(new Employee("Sipho", "Dlamini", 34, 'M'));
    Team* t2 = new Team(2);
    t2->addMember(new Employee("Anna", "Botha", 41, 'F'));
    t2->addMember(new Employee("Ravi", "Naidoo", 38, 'M'));
    Team* t3 = new Team(2);
    t3->addMember(new Employee("Lebo", "Nkosi", 25, 'F'));
    d->addTeam(t1);
    d->addTeam(t2);
    d->addTeam(t3);
    delete (*d)[1];
    (*d)[1] = NULL;
    cout << *d;

    cout << "Employees from team 0: " << d->totalEmployees(0) << endl;
    cout << "Employees from team 2: " << d->totalEmployees(2) << endl;
    cout << "Employees from team 3: " << d->totalEmployees(3) << endl;

    (*d)[0]->removeMember(0);
    cout << "After removing a member of team 0: " << d->totalEmployees(0) << endl;
    delete d;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Department of size 4:
Slot 0: Team of size 3:
  0: Thandi Mokoena, 29, F, ID: none
  1: Sipho Dlamini, 34, M, ID: none
  2: empty
Slot 1: empty
Slot 2: Team of size 2:
  0: Lebo Nkosi, 25, F, ID: none
  1: empty
Slot 3: empty
Employees from team 0: 3
Employees from team 2: 1
Employees from team 3: 0
After removing a member of team 0: 2
*/
