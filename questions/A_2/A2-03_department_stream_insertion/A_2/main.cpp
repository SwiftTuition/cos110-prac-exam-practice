
#include <iostream>

#include "Department.h"
#include "Development.h"
#include "Employee.h"
#include "HR.h"
#include "Team.h"

using namespace std;

int main() {
    Department* dev = new Development(2);
    Team* backend = new Team(2);
    backend->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    backend->addMember(new Employee("Sipho", "Dlamini", 35, 'M'));
    dev->addTeam(backend);

    Department* hr = new HR(3);
    Team* people = new Team(1);
    people->addMember(new Employee("Anna", "Botha", 41, 'F'));
    hr->addTeam(people);

    cout << *dev;
    cout << *hr;

    delete dev;
    delete hr;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Department: Development (cost R50000)
Team (2/2):
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
Department: HR (cost R12000)
Team (1/1):
  Anna Botha, 41, F, ID: none
*/
