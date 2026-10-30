#include "Company.h"

float Company::totalCost(Node<Department*>* curr) {
    // Base case: past the last node, so there is nothing to add.
    if (curr == NULL) {
        return 0;
    }
    // Cost of the department in this node (a NULL department adds 0).
    float here = 0;
    if (curr->getData() != NULL) {
        here = curr->getData()->costToCompany();
    }
    // Recursive case: add the cost of the departments after this node.
    return here + totalCost(curr->next());
}
