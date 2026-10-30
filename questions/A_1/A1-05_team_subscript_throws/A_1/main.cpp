
#include <iostream>

#include "Employee.h"
#include "Exception.h"
#include "Team.h"

using namespace std;

void show(Team& team, int index) {
    try {
        const Employee& e = team[index];
        cout << "[" << index << "] " << e << endl;
    } catch (Exception& ex) {
        cout << "[" << index << "] Caught: " << ex.what() << endl;
    }
}

int main() {
    Team* team = new Team(3);
    team->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    team->addMember(new Employee("Sipho", "Dlamini", 35, 'M'));

    show(*team, 0);
    show(*team, 1);
    show(*team, 2);
    show(*team, 3);
    show(*team, -1);

    delete team;
    return 0;
}
/*
ExpectedOutput:
*/
/*
[0] Thandi Mokoena, 29, F, ID: none
[1] Sipho Dlamini, 35, M, ID: none
[2] Caught: No employee at this index
[3] Caught: Index out of bounds
[-1] Caught: Index out of bounds
*/
