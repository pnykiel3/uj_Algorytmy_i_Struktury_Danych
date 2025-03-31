#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    int priority; // dodano priorytet
    Node<T>* next;
    explicit Node(T val, int p) : data(val), priority(p), next(nullptr) {}

};

template <typename T>
class priorityQueue {
private:
    Node<T>* head;

public:
    priorityQueue() : head(nullptr) {}

    explicit priorityQueue(T value, int priority) : head(new Node<T>(value, priority)) {}

    ~priorityQueue() {
        Node<T>* current = head;
        while (current) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void push(T value, int p) {
        if (exists(value)) {
            return;
        }

        auto* newNode = new Node<T>(value, p);

        if (!head || head->priority > p) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node<T>* current = head;
        while (current->next && current->next->priority < p) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    T pop() {
        if (!head) return nullptr;
        Node<T>* temp = head;
        head = head->next;
        return temp->data;
    }

    // Wypisanie elementów zbioru
    void print() const {
        Node<T>* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    bool exists(T value) const {
        Node<T>* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

};

#endif // PRIORITYQUEUE_H