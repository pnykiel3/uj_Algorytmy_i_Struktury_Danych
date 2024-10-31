// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *head, *tail;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList(); // tu trzeba wyczyscic wezly

    DoubleList(const DoubleList& other); // copy constructor
    // usage:   DoubleList<int> list2(list1);

    DoubleList& operator=(const DoubleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    bool empty() const { return head == nullptr; }
    std::size_t size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_back(const T& item); // O(1)
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(1)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void display_reversed(); // O(n)


};

template <typename T>
void DoubleList<T>::push_front(const T& item) {
    DoubleNode<T> *newNode = new DoubleNode<T>(item, head, nullptr);
    if (!empty()) {
        head->prev = newNode;
    } else {
        tail = newNode; // jeśli lista była pusta
    }
    head = newNode;
}

template <typename T>
void DoubleList<T>::push_back(const T& item) {
    DoubleNode<T> *newNode = new DoubleNode<T>(item, nullptr, tail);
    if (!empty()) {
        tail->next = newNode;
    } else {
        head = newNode; // jeśli lista była pusta
    }
    tail = newNode;
}


template <typename T>
std::size_t DoubleList<T>::size() const {
    int count = 0;
    for (DoubleNode<T> *node = head; node != nullptr; node = node->next) {
        count++;
    }
    return count;
}


template <typename T>
void DoubleList<T>::pop_front() {
    assert(!empty());
    DoubleNode<T> *node = head;
    if (head == tail) { // jeden węzeł na liście
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr; // ustawiamy prev nowego head na nullptr
    }
    delete node;
}

template <typename T>
void DoubleList<T>::pop_back() {
    assert(!empty());
    DoubleNode<T> *node = tail;
    if (head == tail) { // jeden węzeł na liście
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr; // ustawiamy next nowego tail na nullptr
    }
    delete node;
}



template <typename T>
void DoubleList<T>::clear() {
    while(!empty()) {
        pop_front();
    }
}


template <typename T>
void DoubleList<T>::display() {
    DoubleNode<T> *node = head;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}


template <typename T>
void DoubleList<T>::display_reversed() {
    DoubleNode<T> *node = tail;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->prev;
    }
    std::cout << std::endl;
}


template <typename T>
DoubleList<T>::~DoubleList() {
    clear();
}


template <typename T>
DoubleList<T>::DoubleList(const DoubleList& other) : head(nullptr), tail(nullptr) {
    DoubleNode<T> *current = other.head;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
}


template <typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList& other) {
    if (this != &other) { // zabezpieczenie przed przydzieleniem do samego siebie
        clear();
        DoubleNode<T> *current = other.head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }
    return *this;
}


#endif

// EOF
