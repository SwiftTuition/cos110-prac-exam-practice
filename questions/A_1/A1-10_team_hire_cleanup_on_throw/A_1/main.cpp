
#include <iostream>

#include "Employee.h"
#include "Exception.h"
#include "Team.h"

using namespace std;

void tryHire(Team& team, string firstName, string surName, int age, char gender, string idNum) {
    try {
        team.hire(firstName, surName, age, gender, idNum);
        cout << "Hired " << firstName << " " << surName << endl;
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
}

int main() {
    Team* team = new Team(2);
    tryHire(*team, "Thandi", "Mokoena", 29, 'F', "9702140123081");
    tryHire(*team, "Sipho", "Dlamini", 35, 'M', "9105220800087");
    tryHire(*team, "Sipho", "Dlamini", 35, 'M', "9105225800087");
    tryHire(*team, "Lebo", "Nkosi", 25, 'F', "0101014999081");
    cout << *team;

    delete team;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Hired Thandi Mokoena
Caught: ID number does not match gender
Hired Sipho Dlamini
Caught: Team is full
Team:
  Thandi Mokoena, 29, F, ID: 9702140123081
  Sipho Dlamini, 35, M, ID: 9105225800087
*/
