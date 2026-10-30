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

// Makes a new node that holds a copy of value, at the front of the list.
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
