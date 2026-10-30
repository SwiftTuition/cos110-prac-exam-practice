#include <iostream>

#include "Employee.h"
#include "Exception.h"
#include "Team.h"

using namespace std;

int main() {
    Team* t = new Team(5);
    t->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    t->addMember(new Employee("Sipho", "Dlamini", 34, 'M'));
    t->addMember(new Employee("Anna", "Botha", 41, 'F'));
    t->addMember(new Employee("Ravi", "Naidoo", 38, 'M'));
    t->removeMember(1);
    cout << *t;

    cout << "Oldest from index 0: " << t->oldest(0) << endl;
    cout << "Oldest from index 3: " << t->oldest(3) << endl;
    cout << "Oldest from index 4: " << t->oldest(4) << endl;

    t->removeMember(2);
    cout << "After removing member 2, from index 0: " << t->oldest(0) << endl;
    delete t;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Team of size 5:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
  2: Anna Botha, 41, F, ID: none
  3: Ravi Naidoo, 38, M, ID: none
  4: empty
Oldest from index 0: 41
Oldest from index 3: 38
Oldest from index 4: 0
After removing member 2, from index 0: 38
*/
