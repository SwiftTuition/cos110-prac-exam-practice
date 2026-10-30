#include "Team.h"

void Team::hire(string firstName, string surName, int age, char gender, string idNum) {
    Employee* newEmployee = new Employee(firstName, surName, age, gender);
    try {
        newEmployee->setIDNum(idNum);
        addMember(newEmployee);
    } catch (Exception& e) {
        // The team did not take the employee, so it is freed here.
        delete newEmployee;
        throw e;  // "throw;" also works: it throws the same exception again
    }
}
