
#include <iostream>

#include "Employee.h"
#include "Team.h"

using namespace std;

int main() {
    Team* north = new Team(3);
    north->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    north->addMember(new Employee("Sipho", "Dlamini", 35, 'M'));
    Team* south = new Team(2);
    south->addMember(new Employee("Anna", "Botha", 41, 'F'));

    Team merged = *north + *south;
    cout << merged;
    cout << *north;
    cout << *south;

    delete north;
    delete south;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Team (3/3):
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
  Anna Botha, 41, F, ID: none
Team (2/3):
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
Team (1/2):
  Anna Botha, 41, F, ID: none
*/
