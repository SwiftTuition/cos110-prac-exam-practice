#include "BinaryStrings.h"

// Removes the first string in the list that is equal to b: the same size and the
// same bit at every index. Returns true if a node was removed, false otherwise.
bool BinaryStrings::remove(const Binary& b) {
    Node<Binary>* prev = NULL;
    Node<Binary>* curr = head;
    while (curr != NULL) {
        // Compare curr's string with b, bit by bit (Binary has no operator==).
        Binary& data = curr->getData();
        bool same = (data.getSize() == b.getSize());
        for (int i = 0; same && i < b.getSize(); i++) {
            if (data[i] != b[i]) {
                same = false;
            }
        }
        if (same) {
            // Unlink curr: at the front, head moves; otherwise prev skips curr.
            if (prev == NULL) {
                head = curr->next();
            } else {
                prev->next() = curr->next();
            }
            // Deleting the node also destroys its Binary (and so its bool array).
            delete curr;
            size--;
            return true;
        }
        prev = curr;
        curr = curr->next();
    }
    return false;
}
