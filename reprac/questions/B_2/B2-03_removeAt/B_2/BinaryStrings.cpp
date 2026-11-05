#include "BinaryStrings.h"

BinaryStrings::BinaryStrings() : head(NULL), size(0) {
}

// Deletes every node. Deleting a node also destroys the Binary inside it.
BinaryStrings::~BinaryStrings() {
    Node<Binary>* curr = head;
    while (curr != NULL) {
        Node<Binary>* temp = curr;
        curr = curr->next();
        delete temp;
    }
}

// The new node holds a copy of b (Node<Binary> stores a Binary, made with the copy constructor).
void BinaryStrings::prepend(const Binary& b) {
    Node<Binary>* newNode = new Node<Binary>(b);
    newNode->next() = head;
    head = newNode;
    size++;
}

Node<Binary>*& BinaryStrings::getHead() {
    return head;
}

// "Pos" means positive here. A binary string counts as positive when its first
// bit (the sign bit) is 0 and it has at least one 1.
int BinaryStrings::calculatePos() {
    int count = 0;
    Node<Binary>* curr = head;
    while (curr != NULL) {
        Binary& b = curr->getData();
        if (b.getSize() > 0 && b[0] == false) {
            for (int i = 1; i < b.getSize(); i++) {
                if (b[i]) {
                    count++;
                    break;
                }
            }
        }
        curr = curr->next();
    }
    return count;
}

int BinaryStrings::getSize() {
    return size;
}

// Prints Empty, or the strings joined by " -> ", for example 000 -> 0011 -> 1101.
ostream& operator<<(ostream& out, const BinaryStrings& list) {
    if (list.head == NULL) {
        out << "Empty";
        return out;
    }
    Node<Binary>* curr = list.head;
    while (curr != NULL) {
        out << curr->getData();
        if (curr->next() != NULL) {
            out << " -> ";
        }
        curr = curr->next();
    }
    return out;
}
