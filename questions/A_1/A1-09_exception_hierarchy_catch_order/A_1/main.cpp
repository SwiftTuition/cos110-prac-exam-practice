
#include <iostream>

#include "Employee.h"
#include "Exception.h"
#include "InvalidIDException.h"
#include "Team.h"

using namespace std;

int main() {
    Team* team = new Team(3);
    team->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    team->addMember(new Employee("Sipho", "Dlamini", 35, 'M'));

    int count = 0;
    if (team->setMemberID(0, "9702140123081")) {
        count++;
    }
    if (team->setMemberID(1, "91052258000")) {
        count++;
    }
    if (team->setMemberID(1, "9105225800O87")) {
        count++;
    }
    if (team->setMemberID(1, "9105220800087")) {
        count++;
    }
    if (team->setMemberID(2, "8503300800089")) {
        count++;
    }
    if (team->setMemberID(1, "9105225800087")) {
        count++;
    }
    cout << "IDs set: " << count << endl;
    cout << *team;

    delete team;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Member 0: ID set to 9702140123081
Member 1: bad ID [91052258000]: ID number must have 13 digits
Member 1: bad ID [9105225800O87]: ID number must contain only digits
Member 1: ID number does not match gender
Member 2: No member at this index
Member 1: ID set to 9105225800087
IDs set: 2
Team:
  Thandi Mokoena, 29, F, ID: 9702140123081
  Sipho Dlamini, 35, M, ID: 9105225800087
*/
