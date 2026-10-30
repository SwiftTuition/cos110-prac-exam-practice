
#include <iostream>

#include "Employee.h"
#include "Team.h"

using namespace std;

int main() {
    Team* team = new Team(1);
    team->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));

    Employee* sipho = new Employee("Sipho", "Dlamini", 35, 'M');
    *team += sipho;
    sipho->setIDNum("9105225800087");
    cout << *team;
    cout << "Main's employee: " << *sipho << endl;

    Employee* anna = new Employee("Anna", "Botha", 41, 'F');
    Employee* lebo = new Employee("Lebo", "Nkosi", 25, 'F');
    (*team += anna) += lebo;
    cout << *team;

    delete sipho;
    delete anna;
    delete lebo;
    delete team;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Team (2/2):
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
Main's employee: Sipho Dlamini, 35, M, ID: 9105225800087
Team (4/4):
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
  Anna Botha, 41, F, ID: none
  Lebo Nkosi, 25, F, ID: none
*/
