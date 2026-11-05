#include "BinaryStrings.h"

// Removes the node at position pos (the head is position 0).
// Returns false, and changes nothing, if pos is not a valid position.
bool BinaryStrings::removeAt(int pos) {
    // Invalid position (this also covers the empty list, where size is 0).
    if (pos < 0 || pos >= size) {
        return false;
    }
    Node<Binary>* temp = NULL;
    if (pos == 0) {
        // Front case: the second node becomes the head.
        temp = head;
        head = head->next();
    } else {
        // Walk to the node before position pos.
        Node<Binary>* prev = head;
        for (int i = 0; i < pos - 1; i++) {
            prev = prev->next();
        }
        // Unlink the node after prev.
        temp = prev->next();
        prev->next() = temp->next();
    }
    // Deleting the node also destroys its Binary (and so its bool array).
    delete temp;
    size--;
    return true;
}
