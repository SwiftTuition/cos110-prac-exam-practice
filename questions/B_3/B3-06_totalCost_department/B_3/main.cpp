#include <iostream>
#include <string>

#include "Company.h"
#include "Department.h"
#include "Development.h"
#include "Employee.h"
#include "HR.h"
#include "List.h"
#include "Marketing.h"
#include "Sales.h"
#include "Team.h"
#include "Templates.h"

using namespace std;

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
    List<int> numbers;
    numbers.prepend(5);
    numbers.prepend(10);
    cout << "totalCost(numbers): " << totalCost(numbers) << endl;

    Company yyra;
    yyra.addDepartment(makeDepartment(new Sales(1), 1));
    yyra.addDepartment(makeDepartment(new Marketing(1), 2));
    yyra.addDepartment(makeDepartment(new Development(1), 1));
    cout << "Company cost: R" << yyra.costToCompany() << endl;

    List<Department*> empty;
    cout << "totalCost(empty): " << totalCost(empty) << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
totalCost(numbers): 0
Company cost: R76000
totalCost(empty): 0
*/
