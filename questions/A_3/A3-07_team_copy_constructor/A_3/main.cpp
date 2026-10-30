#include <iostream>

#include "Employee.h"
#include "Exception.h"
#include "Team.h"

using namespace std;

int main() {
    Team* a = new Team(3);
    a->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    a->addMember(new Employee("Sipho", "Dlamini", 34, 'M'));
    a->addMember(new Employee("Anna", "Botha", 41, 'F'));
    a->removeMember(1);
    cout << "Team a:" << endl << *a;

    Team* b = new Team(*a);
    cout << "Team b, a copy of a:" << endl << *b;

    a->removeMember(0);
    cout << "Team a after removing member 0:" << endl << *a;
    cout << "Team b has not changed:" << endl << *b;

    delete a;
    delete b;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Team a:
Team of size 3:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
  2: Anna Botha, 41, F, ID: none
Team b, a copy of a:
Team of size 3:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
  2: Anna Botha, 41, F, ID: none
Team a after removing member 0:
Team of size 3:
  0: empty
  1: empty
  2: Anna Botha, 41, F, ID: none
Team b has not changed:
Team of size 3:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
  2: Anna Botha, 41, F, ID: none
*/
