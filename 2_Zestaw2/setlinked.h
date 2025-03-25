#ifndef SETLINKED_H
#define SETLINKED_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    explicit Node(T val) : data(val), next(nullptr) {}


    Node<T>* getNext() {
        return next;
    }
};

template <typename T>
class setLinked {
private:
    Node<T>* head;

public:
    setLinked() : head(nullptr) {}

    explicit setLinked(T value) : head(new Node<T>(value)) {}

    ~setLinked() {
        Node<T>* current = head;
        while (current) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }

    bool exists(T value) const {
        Node<T>* current = head;
        while (current) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    void insert(T value) {
        if (exists(value)) {
            return;
        }

        Node<T>* newNode = new Node<T>(value);

        if (!head || head->data > value) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node<T>* current = head;
        while (current->next && current->next->data < value) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void remove(T value) {
        if (!head) {
            std::cout << "[remove] Zbiór jest pusty!" << std::endl;
            return;
        }

        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node<T>* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        if (current->next) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            std::cout << "[remove] Element " << value << " nie istnieje w zbiorze!" << std::endl;
        }
    }

    // Suma zbiorów (A ∪ B)
    setLinked<T> sum(const setLinked<T>& other) const {
        setLinked<T> result;
        Node<T>* current = head;

        while (current) {
            result.insert(current->data);
            current = current->next;
        }

        current = other.head;

        while (current) {
            result.insert(current->data);
            current = current->next;
        }

        return result;
    }

    // Część wspólna (A ∩ B)
    setLinked<T> intersection(const setLinked<T>& other) const {
        setLinked<T> result;
        Node<T>* current = head;
        while (current) {
            if (other.exists(current->data)) {
                result.insert(current->data);
            }
            current = current->next;
        }
        return result;
    }

    // Różnica zbiorów (A - B)
    setLinked<T> complement(const setLinked<T>& other) const {
        setLinked<T> result;
        Node<T>* current = head;
        while (current) {
            if (!other.exists(current->data)) {
                result.insert(current->data);
            }
            current = current->next;
        }
        return result;
    }

    // Sprawdzenie równości zbiorów
    bool equals(const setLinked<T>& other) const {
        Node<T>* current1 = head;
        Node<T>* current2 = other.head;

        while (current1 && current2) {
            if (current1->data != current2->data) return false;
            current1 = current1->next;
            current2 = current2->next;
        }

        return current1 == nullptr && current2 == nullptr;
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

    Node<T>* getHead() {
        return head;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

};

#endif // SETLINKED_H
