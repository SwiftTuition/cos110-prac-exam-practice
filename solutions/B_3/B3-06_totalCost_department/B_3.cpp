#include "Templates.h"

// The total monthly cost of every department in the list. NULL entries are skipped.
template <>
float totalCost<Department*>(List<Department*>& list) {
    float total = 0;
    Node<Department*>* curr = list.head();
    while (curr != NULL) {
        Department* department = curr->getData();
        if (department != NULL) {
            total += department->costToCompany();   // virtual: the subclass rule is used
        }
        curr = curr->next();
    }
    return total;
}
