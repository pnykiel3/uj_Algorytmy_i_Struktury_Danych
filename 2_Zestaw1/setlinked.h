#ifndef SETLINKED_H
#define SETLINKED_H

#include <iostream>


struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class setLinked {
private:
    Node* head;

public:
    setLinked() : head(nullptr) {}

    ~setLinked() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

    bool exists(int value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    void insert(int value) {
        if (exists(value)) {
          return;
        }

        Node* newNode = new Node(value);

        if (!head || head->data > value) { // Wstawienie na początek
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && current->next->data < value) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void remove(int value) {

        if (!head) {
            std::cout << "[remove]    Zbiór jest pusty!" << std::endl;
            return;
        }

        // gdy usuwamy pierwszy element
        if (head->data == value) {
            Node* temp = head; // potrzebne aby nie powstał wyciek pamięci
            head = head->next;
            delete temp;
            return;
        }

        //pozostałe przypadki
        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }



        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            std::cout << "[remove]    Element " << value << " nie istnieje w zbiorze!" << std::endl;
        }
    }

    // Suma zbiorów (A ∪ B)
    setLinked sum(const setLinked& other) const {
        setLinked result;

        Node* current = head;

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
    setLinked intersection(const setLinked& other) const {
        setLinked result;
        Node* current = head;
        while (current) {
            if (other.exists(current->data)) {
                result.insert(current->data);
            }
            current = current->next;
        }
        return result;
    }

    // Różnica zbiorów (A - B)
    setLinked complement(const setLinked& other) const {
        setLinked result;
        Node* current = head;
        while (current) {
            if (!other.exists(current->data)) {
                result.insert(current->data);
            }
            current = current->next;
        }
        return result;
    }

    // Sprawdzenie równości zbiorów
    bool equals(const setLinked& other) const {
        Node* current1 = head;
        Node* current2 = other.head;

        while (current1 && current2) {
            if (current1->data != current2->data) return false;
            current1 = current1->next;
            current2 = current2->next;
        }

        return current1 == nullptr && current2 == nullptr;
    }

    // Wypisanie elementów zbioru
    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

#endif // SETLINKED_H
