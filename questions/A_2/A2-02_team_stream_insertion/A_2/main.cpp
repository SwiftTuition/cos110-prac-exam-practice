
#include <iostream>

#include "Employee.h"
#include "Team.h"

using namespace std;

int main() {
    Team* team = new Team(3);
    Employee* thandi = new Employee("Thandi", "Mokoena", 29, 'F');
    thandi->setIDNum("9702140123081");
    team->addMember(thandi);
    team->addMember(new Employee("Sipho", "Dlamini", 35, 'M'));
    cout << *team;

    team->removeMember(0);
    cout << *team;

    Team* empty = new Team(2);
    cout << *empty;

    delete team;
    delete empty;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Team (2/3):
  Thandi Mokoena, 29, F, ID: 9702140123081
  Sipho Dlamini, 35, M, ID: none
Team (1/3):
  Sipho Dlamini, 35, M, ID: none
Team (0/2):
  (no members)
*/
