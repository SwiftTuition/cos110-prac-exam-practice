
#include <iostream>

#include "Employee.h"
#include "Exception.h"
#include "Team.h"

using namespace std;

int main() {
    Team* team = new Team(3);
    team->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    team->addMember(new Employee("Sipho", "Dlamini", 35, 'M'));

    string ids[4] = {"9702140123081", "9105220800087", "8503300800089", "8001010001084"};
    int count = team->assignIDs(ids, 4);
    cout << "IDs set: " << count << endl;
    cout << *team;

    delete team;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Slot 0: Thandi Mokoena -> 9702140123081
Slot 1: Sipho Dlamini -> Error: ID number does not match gender
Slot 2: empty
Slot 3: no such slot
IDs set: 1
Team:
  Thandi Mokoena, 29, F, ID: 9702140123081
  Sipho Dlamini, 35, M, ID: none
*/
