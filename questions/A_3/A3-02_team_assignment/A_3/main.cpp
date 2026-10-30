#include <iostream>

#include "Employee.h"
#include "Exception.h"
#include "Team.h"

using namespace std;

int main() {
    Team* a = new Team(2);
    a->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));

    Team* b = new Team(3);
    b->addMember(new Employee("Sipho", "Dlamini", 34, 'M'));
    b->addMember(new Employee("Anna", "Botha", 41, 'F'));
    b->addMember(new Employee("Ravi", "Naidoo", 38, 'M'));
    b->removeMember(1);

    cout << "Team a before:" << endl << *a;
    cout << "Team b:" << endl << *b;

    *a = *b;

    cout << "Team a after *a = *b:" << endl << *a;

    b->removeMember(0);
    cout << "Team b after removing member 0:" << endl << *b;
    cout << "Team a has not changed:" << endl << *a;

    delete a;
    delete b;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Team a before:
Team of size 2:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
Team b:
Team of size 3:
  0: Sipho Dlamini, 34, M, ID: none
  1: empty
  2: Ravi Naidoo, 38, M, ID: none
Team a after *a = *b:
Team of size 3:
  0: Sipho Dlamini, 34, M, ID: none
  1: empty
  2: Ravi Naidoo, 38, M, ID: none
Team b after removing member 0:
Team of size 3:
  0: empty
  1: empty
  2: Ravi Naidoo, 38, M, ID: none
Team a has not changed:
Team of size 3:
  0: Sipho Dlamini, 34, M, ID: none
  1: empty
  2: Ravi Naidoo, 38, M, ID: none
*/
