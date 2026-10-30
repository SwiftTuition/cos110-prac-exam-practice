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

    cout << "Members from index 0: " << t->countMembers(0) << endl;
    cout << "Members from index 2: " << t->countMembers(2) << endl;
    cout << "Members from index 4: " << t->countMembers(4) << endl;

    t->removeMember(0);
    cout << "After removing member 0, from index 0: " << t->countMembers(0) << endl;
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
Members from index 0: 3
Members from index 2: 2
Members from index 4: 0
After removing member 0, from index 0: 2
*/
