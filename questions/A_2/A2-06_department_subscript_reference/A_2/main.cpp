
#include <iostream>

#include "Department.h"
#include "Development.h"
#include "Employee.h"
#include "Exception.h"
#include "Team.h"

using namespace std;

int main() {
    Department* dev = new Development(3);
    (*dev)[0] = new Team(2);
    (*dev)[0]->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    (*dev)[0]->addMember(new Employee("Sipho", "Dlamini", 35, 'M'));
    (*dev)[2] = new Team(1);
    (*dev)[2]->addMember(new Employee("Anna", "Botha", 41, 'F'));
    cout << *dev;

    Team* temp = (*dev)[0];
    (*dev)[0] = (*dev)[2];
    (*dev)[2] = temp;
    cout << *dev;

    try {
        (*dev)[3] = NULL;
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }

    delete dev;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Development (cost R75000)
Team:
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
Team:
  Anna Botha, 41, F, ID: none
Development (cost R75000)
Team:
  Anna Botha, 41, F, ID: none
Team:
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
Caught: Index out of bounds
*/
