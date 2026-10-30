template <class T>
List<T>::List() : headNode(NULL), size(0) {
}

// The destructor uses clear() to delete every node.
template <class T>
List<T>::~List() {
    clear();
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
