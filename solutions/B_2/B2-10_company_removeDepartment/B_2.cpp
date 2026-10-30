#include "Company.h"

// Removes the first department (in list order) whose name is name.
// The company owns its departments, so the Department object is deleted too.
bool Company::removeDepartment(string name) {
    Node<Department*>* curr = departments.head();
    while (curr != NULL) {
        Department* department = curr->getData();
        if (department->getName() == name) {
            // Unlink and delete the node first (curr is not used after this),
            // then delete the Department that the pointer points to.
            departments.remove(department);
            delete department;
            return true;
        }
        curr = curr->next();
    }
    return false;
}
