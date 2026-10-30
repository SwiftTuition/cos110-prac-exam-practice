
#include <iostream>

#include "Employee.h"
#include "Exception.h"

using namespace std;

void tryID(Employee* e, string id) {
    try {
        e->setIDNum(id);
        cout << "Accepted: " << *e << endl;
    } catch (Exception& ex) {
        cout << "Rejected " << id << ": " << ex.what() << endl;
    }
}

int main() {
    Employee* thandi = new Employee("Thandi", "Mokoena", 29, 'F');
    Employee* sipho = new Employee("Sipho", "Dlamini", 35, 'M');
    Employee* anna = new Employee("Anna", "Botha", 41, 'F');
    Employee* bongani = new Employee("Bongani", "Zulu", 30, 'M');

    tryID(thandi, "9702140123081");
    tryID(sipho, "9105225800087");
    tryID(anna, "8503305800089");
    tryID(anna, "8503300800089");
    tryID(bongani, "9001015800083");
    tryID(bongani, "9601015800083");

    delete thandi;
    delete sipho;
    delete anna;
    delete bongani;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Accepted: Thandi Mokoena, 29, F, ID: 9702140123081
Accepted: Sipho Dlamini, 35, M, ID: 9105225800087
Rejected 8503305800089: ID number does not match gender
Accepted: Anna Botha, 41, F, ID: 8503300800089
Rejected 9001015800083: ID number does not match age
Accepted: Bongani Zulu, 30, M, ID: 9601015800083
*/
