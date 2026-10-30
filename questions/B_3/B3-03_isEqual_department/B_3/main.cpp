#include <iostream>
#include <string>

#include "Department.h"
#include "Development.h"
#include "Employee.h"
#include "HR.h"
#include "Marketing.h"
#include "Sales.h"
#include "Team.h"
#include "Templates.h"

using namespace std;

void compare(string label, bool result) {
    cout << label << ": " << (result ? "equal" : "not equal") << endl;
}

Department* makeDepartment(Department* department, int people) {
    if (people > 0) {
        Team* team = new Team(people);
        for (int i = 0; i < people; i++) {
            team->addMember(new Employee("Worker", "Number", 20 + i, 'F'));
        }
        department->addTeam(team);
    }
    return department;
}

int main() {
    compare("5 and 5", isEqual(5, 5));
    compare("5 and 6", isEqual(5, 6));
    compare("HR and HR", isEqual(string("HR"), string("HR")));

    Department* marketing = makeDepartment(new Marketing(1), 2);
    Department* hr = makeDepartment(new HR(1), 3);
    Department* sales = makeDepartment(new Sales(1), 1);
    cout << "Marketing R" << marketing->costToCompany() << ", HR R" << hr->costToCompany()
         << ", Sales R" << sales->costToCompany() << endl;
    compare("Marketing and HR", isEqual(marketing, hr));
    compare("Sales and HR", isEqual(sales, hr));

    delete marketing;
    delete hr;
    delete sales;
    return 0;
}
/*
ExpectedOutput:
*/
/*
5 and 5: equal
5 and 6: not equal
HR and HR: equal
Marketing R36000, HR R36000, Sales R15000
Marketing and HR: equal
Sales and HR: not equal
*/
