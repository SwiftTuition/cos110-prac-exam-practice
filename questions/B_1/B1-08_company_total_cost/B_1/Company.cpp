#include "Company.h"

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

// New departments go to the front of the list.
void Company::addDepartment(Department* department) {
    departments.prepend(department);
}

List<Department*>& Company::getDepartments() {
    return departments;
}

float Company::costToCompany() {
    return totalCost(departments.head());
}

ostream& operator<<(ostream& out, Company& c) {
    out << "Company with " << c.departments.getSize() << " departments" << endl;
    Node<Department*>* curr = c.departments.head();
    while (curr != NULL) {
        if (curr->getData() == NULL) {
            out << "(no department)" << endl;
        } else {
            out << *curr->getData();
        }
        curr = curr->next();
    }
    return out;
}
