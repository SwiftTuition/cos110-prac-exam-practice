#include "Department.h"
#include "List.h"

// For a list of Department pointers, print each Department, not its address.
template <>
void List<Department*>::printAll() {
    if (headNode == NULL) {
        cout << "Empty List" << endl;
        return;
    }
    Node<Department*>* curr = headNode;
    int index = 0;
    while (curr != NULL) {
        Department* department = curr->getData();
        if (department == NULL) {
            cout << index << ": No department" << endl;
        } else {
            cout << index << ": " << *department;   // operator<< ends its own lines
        }
        curr = curr->next();
        index++;
    }
}
