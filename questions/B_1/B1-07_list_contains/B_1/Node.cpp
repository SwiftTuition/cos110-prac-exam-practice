// The node owns data. It does not delete the next node.
template <class T>
Node<T>::Node(T* data) : data(data), nextNode(NULL) {
}

template <class T>
Node<T>::~Node() {
    delete data;
    nextNode = NULL;
}

template <class T>
const T& Node<T>::getData() {
    return *data;
}

template <class T>
Node<T>*& Node<T>::next() {
    return nextNode;
}
