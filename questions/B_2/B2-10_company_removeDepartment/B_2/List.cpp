template <class T>
List<T>::List() : headNode(NULL), size(0) {
}

template <class T>
List<T>::~List() {
    Node<T>* curr = headNode;
    while (curr != NULL) {
        Node<T>* temp = curr;
        curr = curr->next();
        delete temp;
    }
}

template <class T>
void List<T>::prepend(T value) {
    Node<T>* newNode = new Node<T>(new T(value));
    newNode->next() = headNode;
    headNode = newNode;
    size++;
}

template <class T>
Node<T>* const& List<T>::head() const {
    return headNode;
}

template <class T>
int List<T>::getSize() {
    return size;
}

// Given: removes the first node that holds value. Returns true if a node was removed.
// For List<Department*> this compares pointers, and it deletes the node only
// (the node deletes its copy of the pointer, not the Department).
template <class T>
bool List<T>::remove(T value) {
    if (headNode == NULL) {
        return false;
    }
    if (headNode->getData() == value) {
        Node<T>* temp = headNode;
        headNode = headNode->next();
        delete temp;
        size--;
        return true;
    }
    Node<T>* prev = headNode;
    Node<T>* curr = headNode->next();
    while (curr != NULL) {
        if (curr->getData() == value) {
            prev->next() = curr->next();
            delete curr;
            size--;
            return true;
        }
        prev = curr;
        curr = curr->next();
    }
    return false;
}

template <class T>
ostream& operator<<(ostream& out, const List<T>& list) {
    if (list.headNode == NULL) {
        out << "Empty List";
        return out;
    }
    Node<T>* curr = list.headNode;
    while (curr->next() != NULL) {
        out << curr->getData() << "->";
        curr = curr->next();
    }
    out << curr->getData();
    return out;
}
