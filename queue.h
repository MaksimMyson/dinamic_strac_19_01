#ifndef QUEUE_H
#define QUEUE_H

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
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;

public:
    Queue();
    ~Queue();

    void Enqueue(const T& value);
    void Dequeue();
    bool IsEmpty() const;
    void Display() const;
};

template <typename T>
Queue<T>::Queue() : front(nullptr), rear(nullptr) {}

template <typename T>
Queue<T>::~Queue() {
    while (!IsEmpty()) {
        Dequeue();
    }
}

template <typename T>
void Queue<T>::Enqueue(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (IsEmpty()) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        newNode->prev = rear;
        rear = newNode;
    }
}

template <typename T>
void Queue<T>::Dequeue() {
    if (!IsEmpty()) {
        Node<T>* temp = front;
        front = front->next;

        if (front) {
            front->prev = nullptr;
        }
        else {
            rear = nullptr;
        }

        delete temp;
    }
    else {
        std::cerr << "Queue is empty. Cannot dequeue from an empty queue." << std::endl;
    }
}

template <typename T>
bool Queue<T>::IsEmpty() const {
    return (front == nullptr);
}

template <typename T>
void Queue<T>::Display() const {
    Node<T>* current = front;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

#endif