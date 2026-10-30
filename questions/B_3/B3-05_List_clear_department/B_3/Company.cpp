#include "Company.h"

Company::Company() {
}

// The company takes ownership of the department.
void Company::addDepartment(Department* department) {
    departments.prepend(department);
}

float Company::costToCompany() {
    float total = 0;
    Node<Department*>* curr = departments.head();
    while (curr != NULL) {
        total += curr->getData()->costToCompany();
        curr = curr->next();
    }
    return total;
}

ostream& operator<<(ostream& out, Company& c) {
    out << "Company with " << c.departments.getSize() << " departments" << endl;
    Node<Department*>* curr = c.departments.head();
    while (curr != NULL) {
        out << *curr->getData();
        curr = curr->next();
    }
    return out;
}
