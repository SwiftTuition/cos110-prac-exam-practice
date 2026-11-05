#ifndef TEMPLATES_H
#define TEMPLATES_H

#include "Binary.h"
#include "Node.h"

using namespace std;

// General template: counts the nodes, from head to the end, whose data is true
// (for numbers: not 0).
template <class T>
int countTrue(Node<T>* head) {
    int count = 0;
    Node<T>* curr = head;
    while (curr != NULL) {
        if (curr->getData()) {
            count++;
        }
        curr = curr->next();
    }
    return count;
}

// Specialisation for Binary. Declared here, after the general template and
// before any use.
template <>
int countTrue<Binary>(Node<Binary>* head);

// In this question B_3.cpp is included here, like a template .cpp file.
// B_3.cpp has its own include guard, so it can also be compiled on its own
// (it is on the g++ line). Read QUESTION.md: the definition must be inline.
#include "B_3.cpp"

#endif
