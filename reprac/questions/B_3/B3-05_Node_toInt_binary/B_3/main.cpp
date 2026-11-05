#include <iostream>

#include "Binary.h"
#include "BinaryStrings.h"
#include "Node.h"

using namespace std;

int main() {
    Node<int> n(7);
    Node<double> d(3.9);
    Node<bool> t(true);
    cout << "Node<int> 7: " << n.toInt() << endl;
    cout << "Node<double> 3.9: " << d.toInt() << endl;
    cout << "Node<bool> true: " << t.toInt() << endl;

    Node<Binary> b(Binary("1010"));
    cout << "Node<Binary> " << b.getData() << ": " << b.toInt() << endl;

    BinaryStrings list;
    list.prepend(Binary("0101"));
    list.prepend(Binary("1101"));
    list.prepend(Binary("0011"));
    list.prepend(Binary("000"));
    cout << list << endl;
    Node<Binary>* curr = list.getHead();
    while (curr != NULL) {
        cout << curr->getData() << " -> " << curr->toInt() << endl;
        curr = curr->next();
    }
    return 0;
}
/*
ExpectedOutput:
*/
/*
Node<int> 7: 7
Node<double> 3.9: 3
Node<bool> true: 1
Node<Binary> 1010: 10
000 -> 0011 -> 1101 -> 0101
000 -> 0
0011 -> 3
1101 -> 13
0101 -> 5
*/
