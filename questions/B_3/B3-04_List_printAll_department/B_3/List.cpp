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

// Prints every value on its own line, with its position in front.
template <class T>
void List<T>::printAll() {
    if (headNode == NULL) {
        cout << "Empty List" << endl;
        return;
    }
    Node<T>* curr = headNode;
    int index = 0;
    while (curr != NULL) {
        cout << index << ": " << curr->getData() << endl;
        curr = curr->next();
        index++;
    }
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
