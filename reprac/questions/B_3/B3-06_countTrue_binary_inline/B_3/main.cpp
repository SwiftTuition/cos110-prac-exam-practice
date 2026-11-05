#include <iostream>

#include "Binary.h"
#include "BinaryStrings.h"
#include "Node.h"
#include "Templates.h"

using namespace std;

int main() {
    // A small chain of Node<int>: 0 -> 3 -> 0 -> -2
    Node<int>* first = new Node<int>(0);
    first->next() = new Node<int>(3);
    first->next()->next() = new Node<int>(0);
    first->next()->next()->next() = new Node<int>(-2);
    cout << "Node<int> chain 0 3 0 -2: " << countTrue(first) << " not zero" << endl;

    BinaryStrings list;
    cout << list << ": " << countTrue(list.getHead()) << " true bits" << endl;
    list.prepend(Binary("0101"));
    list.prepend(Binary("1101"));
    list.prepend(Binary("0011"));
    list.prepend(Binary("000"));
    cout << list << ": " << countTrue(list.getHead()) << " true bits" << endl;
    cout << "from the third node: " << countTrue(list.getHead()->next()->next()) << " true bits" << endl;

    Node<int>* curr = first;
    while (curr != NULL) {
        Node<int>* temp = curr;
        curr = curr->next();
        delete temp;
    }
    return 0;
}
/*
ExpectedOutput:
*/
/*
Node<int> chain 0 3 0 -2: 2 not zero
Empty: 0 true bits
000 -> 0011 -> 1101 -> 0101: 7 true bits
from the third node: 5 true bits
*/
