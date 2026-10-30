
#include <iostream>

#include "Employee.h"
#include "Exception.h"
#include "Team.h"

using namespace std;

void printFirstAndLast(const Team& team, int last) {
    const Employee& first = team[0];
    const Employee& lastOne = team[last];
    cout << "First: " << first << endl;
    cout << "Last: " << lastOne << endl;
}

int main() {
    Team* team = new Team(3);
    team->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    team->addMember(new Employee("Sipho", "Dlamini", 35, 'M'));
    team->addMember(new Employee("Anna", "Botha", 41, 'F'));

    printFirstAndLast(*team, 2);
    cout << (*team)[1] << endl;
    try {
        const Employee& e = (*team)[3];
        cout << e << endl;
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }

    delete team;
    return 0;
}
/*
ExpectedOutput:
*/
/*
First: Thandi Mokoena, 29, F, ID: none
Last: Anna Botha, 41, F, ID: none
Sipho Dlamini, 35, M, ID: none
Caught: Index out of bounds
*/
