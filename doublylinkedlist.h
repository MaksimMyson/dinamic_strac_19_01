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

#endif