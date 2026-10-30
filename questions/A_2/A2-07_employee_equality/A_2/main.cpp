
#include <iostream>
#include <string>

#include "Employee.h"

using namespace std;

void compare(string label, const Employee& x, const Employee& y) {
    bool same = (x == y);
    bool different = (x != y);
    cout << label << ": == gives " << (same ? "true" : "false") << ", != gives " << (different ? "true" : "false") << endl;
}

int main() {
    Employee* a = new Employee("Thandi", "Mokoena", 29, 'F');
    Employee* b = new Employee("Thandi", "Mokoena", 29, 'F');
    compare("a, b (no IDs)", *a, *b);

    a->setIDNum("9702140123081");
    b->setIDNum("9702140123081");
    compare("a, b (same ID)", *a, *b);

    Employee* c = new Employee("Thandeka", "Mokoena", 29, 'F');
    c->setIDNum("9702140123082");
    compare("a, c (different IDs)", *a, *c);

    delete a;
    delete b;
    delete c;
    return 0;
}
/*
ExpectedOutput:
*/
/*
a, b (no IDs): == gives true, != gives false
a, b (same ID): == gives true, != gives false
a, c (different IDs): == gives false, != gives true
*/
