#include "Department.h"
#include "List.h"

// For a list of Department pointers, the list owns the Departments:
// delete each Department, then its node.
template <>
void List<Department*>::clear() {
    Node<Department*>* curr = headNode;
    while (curr != NULL) {
        Node<Department*>* temp = curr;
        curr = curr->next();
        delete temp->getData();   // the Department (deleting NULL does nothing)
        delete temp;              // the node, which deletes its copy of the pointer
    }
    headNode = NULL;
    size = 0;
}
