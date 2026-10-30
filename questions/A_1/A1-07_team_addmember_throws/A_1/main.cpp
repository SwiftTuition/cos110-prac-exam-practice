
#include <iostream>

#include "Employee.h"
#include "Exception.h"
#include "Team.h"

using namespace std;

int main() {
    Team* team = new Team(2);
    Employee* thandi = new Employee("Thandi", "Mokoena", 29, 'F');
    Employee* sipho = new Employee("Sipho", "Dlamini", 35, 'M');
    Employee* lebo = new Employee("Lebo", "Nkosi", 25, 'F');

    team->addMember(thandi);
    try {
        team->addMember(thandi);
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    team->addMember(sipho);
    try {
        team->addMember(lebo);
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
        delete lebo;  // the team did not take lebo, so main still owns lebo
    }
    try {
        team->addMember(NULL);
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }

    cout << "Members: " << team->getMemberCount() << endl;
    cout << *team;
    delete team;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Caught: Employee is already in the team
Caught: Team is full
Caught: Employee is NULL
Members: 2
Team:
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
*/
