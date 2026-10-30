#include "Company.h"
#include "Templates.h"

Company::Company() {
}

// The list frees its nodes, but the Departments are only pointed to, so the company deletes them.
Company::~Company() {
    Node<Department*>* curr = departments.head();
    while (curr != NULL) {
        delete curr->getData();
        curr = curr->next();
    }
}

void Company::addDepartment(Department* department) {
    departments.prepend(department);
}

// Uses the totalCost specialization for Department*.
float Company::costToCompany() {
    return totalCost(departments);
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
