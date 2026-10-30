
#include <iostream>

#include "Department.h"
#include "Employee.h"
#include "Exception.h"
#include "Sales.h"
#include "Team.h"

using namespace std;

int main() {
    Department* sales = new Sales(3);

    Team* north = new Team(2);
    north->addMember(new Employee("Thandi", "Mokoena", 29, 'F'));
    north->addMember(new Employee("Sipho", "Dlamini", 35, 'M'));
    sales->addTeam(north);

    (*sales)[2] = new Team(1);
    (*sales)[2]->addMember(new Employee("Anna", "Botha", 41, 'F'));

    if ((*sales)[1] == NULL) {
        cout << "Slot 1 is empty" << endl;
    }
    cout << *sales;

    try {
        (*sales)[-1];
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
    }

    Team* extra = new Team(1);
    try {
        (*sales)[3] = extra;
        cout << "Extra team added" << endl;
    } catch (Exception& e) {
        cout << "Caught: " << e.what() << endl;
        delete extra;
    }

    delete sales;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Slot 1 is empty
Sales (cost R45000)
Team:
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
Team:
  Anna Botha, 41, F, ID: none
Caught: Negative index
Caught: Index too large
*/
