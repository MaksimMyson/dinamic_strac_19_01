#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void AddToHead(const T& value);
    void AddToTail(const T& value);
    void DeleteFromHead();
    void DeleteFromTail();
    void DeleteAll();
    void Show() const;

    void InsertAtPosition(const T& value, int position);
    void DeleteAtPosition(int position);
    int SearchElement(const T& value) const;
    int ReplaceElement(const T& oldValue, const T& newValue);
    void Reverse();

    DoublyLinkedList<T> Clone() const;
    DoublyLinkedList<T> operator+(const DoublyLinkedList<T>& otherList) const;
    DoublyLinkedList<T> operator*(const DoublyLinkedList<T>& otherList) const;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    DeleteAll();
}

template <typename T>
void DoublyLinkedList<T>::AddToHead(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (!head) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

template <typename T>
void DoublyLinkedList<T>::AddToTail(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (!tail) {
        head = tail = newNode;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

template <typename T>
void DoublyLinkedList<T>::DeleteFromHead() {
    if (!head) {
        return;
    }

    Node<T>* temp = head;
    head = head->next;

    if (!head) {
        tail = nullptr;
    }
    else {
        head->prev = nullptr;
    }

    delete temp;
}

template <typename T>
void DoublyLinkedList<T>::DeleteFromTail() {
    if (!tail) {
        return;
    }

    Node<T>* temp = tail;
    tail = tail->prev;

    if (!tail) {
        head = nullptr;
    }
    else {
        tail->next = nullptr;
    }

    delete temp;
}

template <typename T>
void DoublyLinkedList<T>::DeleteAll() {
    while (head) {
        DeleteFromHead();
    }
}

template <typename T>
void DoublyLinkedList<T>::Show() const {
    Node<T>* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
void DoublyLinkedList<T>::InsertAtPosition(const T& value, int position) {
    if (position < 0) {
        std::cerr << "Invalid position. Position should be a non-negative integer." << std::endl;
        return;
    }

    Node<T>* newNode = new Node<T>(value);

    if (position == 0) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else {
        Node<T>* current = head;
        int currentPosition = 0;

        while (current && currentPosition < position - 1) {
            current = current->next;
            currentPosition++;
        }

        if (!current) {
            std::cerr << "Invalid position. Position exceeds the size of the list." << std::endl;
            delete newNode;
            return;
        }

        newNode->next = current->next;
        newNode->prev = current;
        current->next = newNode;

        if (newNode->next) {
            newNode->next->prev = newNode;
        }
        else {
            tail = newNode;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::DeleteAtPosition(int position) {
    if (position < 0) {
        std::cerr << "Invalid position. Position should be a non-negative integer." << std::endl;
        return;
    }

    if (!head) {
        std::cerr << "List is empty. Cannot delete from an empty list." << std::endl;
        return;
    }

    if (position == 0) {
        DeleteFromHead();
    }
    else {
        Node<T>* current = head;
        int currentPosition = 0;

        while (current && currentPosition < position) {
            current = current->next;
            currentPosition++;
        }

        if (!current) {
            std::cerr << "Invalid position. Position exceeds the size of the list." << std::endl;
            return;
        }

        current->prev->next = current->next;

        if (current->next) {
            current->next->prev = current->prev;
        }
        else {
            tail = current->prev;
        }

        delete current;
    }
}

template <typename T>
int DoublyLinkedList<T>::SearchElement(const T& value) const {
    Node<T>* current = head;
    int position = 0;

    while (current) {
        if (current->data == value) {
            return position;
        }

        current = current->next;
        position++;
    }

    return -1; // ?? ????????
}

template <typename T>
int DoublyLinkedList<T>::ReplaceElement(const T& oldValue, const T& newValue) {
    Node<T>* current = head;
    int count = 0;

    while (current) {
        if (current->data == oldValue) {
            current->data = newValue;
            count++;
        }

        current = current->next;
    }

    return count;
}

template <typename T>
void DoublyLinkedList<T>::Reverse() {
    Node<T>* current = head;
    Node<T>* temp = nullptr;

    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp) {
        head = temp->prev;
    }
}

template <typename T>
DoublyLinkedList<T> DoublyLinkedList<T>::Clone() const {
    DoublyLinkedList<T> cloneList;
    Node<T>* current = head;

    while (current) {
        cloneList.AddToTail(current->data);
        current = current->next;
    }

    return cloneList;
}

template <typename T>
DoublyLinkedList<T> DoublyLinkedList<T>::operator+(const DoublyLinkedList<T>& otherList) const {
    DoublyLinkedList<T> result;
    Node<T>* current = head;

    while (current) {
        result.AddToTail(current->data);
        current = current->next;
    }

    current = otherList.head;

    while (current) {
        result.AddToTail(current->data);
        current = current->next;
    }

    return result;
}

template <typename T>
DoublyLinkedList<T> DoublyLinkedList<T>::operator*(const DoublyLinkedList<T>& otherList) const {
    DoublyLinkedList<T> result;
    Node<T>* current = head;

    while (current) {
        if (otherList.SearchElement(current->data) != -1) {
            result.AddToTail(current->data);
        }
        current = current->next;
    }

    return result;
}

#endif