#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>

template <typename T>
class Array {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;
    int capacity;
    int grow;

    void ExpandCapacity(int newSize);

public:
    Array() : head(nullptr), tail(nullptr), size(0), capacity(0), grow(1) {}
    ~Array();

    int GetSize() const;
    void SetSize(int newSize, int newGrow = 1);
    int GetUpperBound() const;
    bool IsEmpty() const;
    void FreeExtra();
    void RemoveAll();
    T GetAt(int index) const;
    void SetAt(int index, const T& value);
    T& operator[](int index);
    const T& operator[](int index) const;
    void Add(const T& value);
    void Append(const Array<T>& otherArray);
    Array<T>& operator=(const Array<T>& otherArray);
    T* GetData() const;
    void InsertAt(int index, const T& value);
    void RemoveAt(int index);
};

template <typename T>
Array<T>::~Array() {
    RemoveAll();
}

template <typename T>
int Array<T>::GetSize() const {
    return size;
}

template <typename T>
void Array<T>::SetSize(int newSize, int newGrow) {
    if (newSize < 0 || newGrow < 0) {
        throw std::invalid_argument("Negative size or growth is not allowed.");
    }

    if (newSize > capacity) {
        ExpandCapacity(newSize);
    }

    size = newSize;
    grow = newGrow;
}

template <typename T>
int Array<T>::GetUpperBound() const {
    return size - 1;
}

template <typename T>
bool Array<T>::IsEmpty() const {
    return size == 0;
}

template <typename T>
void Array<T>::FreeExtra() {
    if (size < capacity) {
        SetSize(size);
    }
}

template <typename T>
void Array<T>::RemoveAll() {
    while (size > 0) {
        RemoveAt(0);
    }
}

template <typename T>
T Array<T>::GetAt(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds.");
    }

    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->data;
}

template <typename T>
void Array<T>::SetAt(int index, const T& value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds.");
    }

    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    current->data = value;
}

template <typename T>
T& Array<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds.");
    }

    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->data;
}

template <typename T>
const T& Array<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds.");
    }

    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->data;
}

template <typename T>
void Array<T>::Add(const T& value) {
    if (size >= capacity) {
        ExpandCapacity(size + grow);
    }

    Node* newNode = new Node(value);
    if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    else {
        head = tail = newNode;
    }

    size++;
}

template <typename T>
void Array<T>::ExpandCapacity(int newSize) {
    if (newSize <= capacity) {
        return;
    }

    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head = tail = nullptr;
    size = 0;
    capacity = newSize;
}

template <typename T>
void Array<T>::Append(const Array<T>& otherArray) {
    for (int i = 0; i < otherArray.GetSize(); ++i) {
        Add(otherArray.GetAt(i));
    }
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& otherArray) {
    if (this != &otherArray) {
        RemoveAll();
        Append(otherArray);
    }
    return *this;
}

template <typename T>
T* Array<T>::GetData() const {
    T* data = new T[size];
    Node* current = head;
    for (int i = 0; i < size; ++i) {
        data[i] = current->data;
        current = current->next;
    }
    return data;
}

template <typename T>
void Array<T>::InsertAt(int index, const T& value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of bounds.");
    }

    if (index == size) {
        Add(value);
        return;
    }

    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    Node* newNode = new Node(value);
    newNode->prev = current->prev;
    newNode->next = current;

    if (current->prev) {
        current->prev->next = newNode;
    }
    else {
        head = newNode;
    }

    current->prev = newNode;
    size++;
}

template <typename T>
void Array<T>::RemoveAt(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds.");
    }

    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    if (current->prev) {
        current->prev->next = current->next;
    }
    else {
        head = current->next;
    }

    if (current->next) {
        current->next->prev = current->prev;
    }
    else {
        tail = current->prev;
    }

    delete current;
    size--;
}

#endif // ARRAY_H
