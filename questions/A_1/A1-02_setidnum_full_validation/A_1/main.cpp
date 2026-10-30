
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

    tryID(thandi, "9702140123081");
    tryID(sipho, "91052258000");
    tryID(sipho, "91O5225800087");
    tryID(sipho, "9113225800087");
    tryID(sipho, "9105005800087");
    tryID(sipho, "9105220800087");
    tryID(sipho, "9105225800087");

    delete thandi;
    delete sipho;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Accepted: Thandi Mokoena, 29, F, ID: 9702140123081
Rejected 91052258000: ID number must have 13 digits
Rejected 91O5225800087: ID number must contain only digits
Rejected 9113225800087: Invalid birth month
Rejected 9105005800087: Invalid birth day
Rejected 9105220800087: ID number does not match gender
Accepted: Sipho Dlamini, 35, M, ID: 9105225800087
*/
