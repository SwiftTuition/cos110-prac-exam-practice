
#include <iostream>

#include "Employee.h"
#include "Team.h"

using namespace std;

int main() {
    Team* team = new Team(4);
    team->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    team->addMember(new Employee("Sipho", "Dlamini", 35, 'M'));
    team->addMember(new Employee("Anna", "Botha", 41, 'F'));

    cout << "Dlamini: " << (*team)("Dlamini") << endl;
    cout << "Botha: " << (*team)("Botha") << endl;
    cout << "Nkosi: " << (*team)("Nkosi") << endl;

    delete team;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Dlamini: 1
Botha: 2
Nkosi: -1
*/
