#include <iostream>

#include "Department.h"
#include "Employee.h"
#include "Exception.h"
#include "Team.h"

using namespace std;

int main() {
    Department* a = new Department(1);
    Team* t1 = new Team(2);
    t1->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    a->addTeam(t1);

    Department* b = new Department(3);
    Team* t2 = new Team(2);
    t2->addMember(new Employee("Sipho", "Dlamini", 34, 'M'));
    t2->addMember(new Employee("Anna", "Botha", 41, 'F'));
    Team* t3 = new Team(1);
    t3->addMember(new Employee("Ravi", "Naidoo", 38, 'M'));
    Team* t4 = new Team(1);
    t4->addMember(new Employee("Lebo", "Nkosi", 25, 'F'));
    b->addTeam(t2);
    b->addTeam(t3);
    b->addTeam(t4);
    delete (*b)[1];
    (*b)[1] = NULL;

    cout << "Department a before:" << endl << *a;
    cout << "Department b:" << endl << *b;

    *a = *b;
    cout << "Department a after *a = *b:" << endl << *a;

    (*b)[0]->removeMember(1);
    delete (*b)[2];
    (*b)[2] = NULL;
    cout << "Department b after the changes:" << endl << *b;
    cout << "Department a has not changed:" << endl << *a;

    delete a;
    delete b;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Department a before:
Department of size 1:
Slot 0: Team of size 2:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
Department b:
Department of size 3:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Slot 2: Team of size 1:
  0: Lebo Nkosi, 25, F, ID: none
Department a after *a = *b:
Department of size 3:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Slot 2: Team of size 1:
  0: Lebo Nkosi, 25, F, ID: none
Department b after the changes:
Department of size 3:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: empty
Slot 1: empty
Slot 2: empty
Department a has not changed:
Department of size 3:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Slot 2: Team of size 1:
  0: Lebo Nkosi, 25, F, ID: none
*/
