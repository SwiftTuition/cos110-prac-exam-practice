#include "BinaryStrings.h"

// Prints the strings from the last node back to curr, one string per line.
void BinaryStrings::printReverse(Node<Binary>* curr) {
    // Base case: past the last node, so there is nothing to print.
    if (curr == NULL) {
        return;
    }
    // Recursive case: print the nodes after this one first, then this node.
    printReverse(curr->next());
    cout << curr->getData() << endl;
}
