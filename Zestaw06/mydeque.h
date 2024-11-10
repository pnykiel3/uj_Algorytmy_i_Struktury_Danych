#ifndef MYDEQUE_H
#define MYDEQUE_H

#include <iostream>
#include <cassert>

template <typename T>
class MyDeque {
    T* tab;
    std::size_t msize; // największa możliwa liczba elementów plus jeden
    std::size_t head; // pierwszy do pobrania
    std::size_t tail; // pierwsza wolna pozycja
public:
    MyDeque();
    MyDeque(std::size_t s); // default constructor
    ~MyDeque();
    MyDeque(const MyDeque& other); // copy constructor
    MyDeque& operator=(const MyDeque& other); // copy assignment operator, return *this
    bool empty() const;
    bool full() const;
    std::size_t size() const;
    std::size_t max_size() const;
    void push_front(const T& item); // dodanie na początek O(1)
    void push_back(const T& item); // dodanie na koniec O(1)
    T& front(); // zwraca poczatek
    T& back(); // zwraca koniec
    void pop_front(); // usuwa początek kolejki O(1)
    void pop_back(); // usuwa koniec kolejki O(1)
    void clear(); // czyszczenie listy z elementów
    void display();
    void display_reversed();
};

template <typename T>
MyDeque<T>::MyDeque() : msize(11), head(0), tail(0) { // domyślny rozmiar = 10 + 1
    tab = new T[msize];
    assert(tab != nullptr);
}

template <typename T>
MyDeque<T>::MyDeque(std::size_t s) : msize(s + 1), head(0), tail(0) {
    tab = new T[msize];
    assert(tab != nullptr);
}

template <typename T>
MyDeque<T>::~MyDeque() {
    delete[] tab;
}

template <typename T>
MyDeque<T>::MyDeque(const MyDeque& other) : msize(other.msize), head(other.head), tail(other.tail) {
    tab = new T[msize];
    for (std::size_t i = 0; i < msize; ++i) {
        tab[i] = other.tab[i];
    }
}

template <typename T>
MyDeque<T>& MyDeque<T>::operator=(const MyDeque& other) {
    if (this != &other) {
        delete[] tab;

        msize = other.msize;
        head = other.head;
        tail = other.tail;

        tab = new T[msize];
        for (std::size_t i = 0; i < msize; ++i) {
            tab[i] = other.tab[i];
        }
    }
    return *this;
}

template <typename T>
bool MyDeque<T>::empty() const {
    return head == tail;
}

template <typename T>
bool MyDeque<T>::full() const {
    return (tail + 1) % msize == head;
}

template <typename T>
std::size_t MyDeque<T>::size() const {
    return (tail - head + msize) % msize;
}

template <typename T>
std::size_t MyDeque<T>::max_size() const {
    return msize - 1;
}

template <typename T>
void MyDeque<T>::push_front(const T& item) {
    assert(!full());
    head = (head + msize - 1) % msize;
    tab[head] = item;
}

template <typename T>
void MyDeque<T>::push_back(const T& item) {
    assert(!full());
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
T& MyDeque<T>::front() {
    return tab[head];
}

template <typename T>
T& MyDeque<T>::back() {
    return tab[(tail + msize - 1) % msize];
}

template <typename T>
void MyDeque<T>::pop_front() {
    assert(!empty());
    head = (head + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_back() {
    assert(!empty());
    tail = (tail + msize - 1) % msize;
}

template <typename T>
void MyDeque<T>::clear() {
    head = tail = 0;
}

template <typename T>
void MyDeque<T>::display() {
    for (std::size_t i = head; i != tail; i = (i + 1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void MyDeque<T>::display_reversed() {
    for (std::size_t i = (tail + msize - 1) % msize; i != head; i = (i + msize - 1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << tab[head] << std::endl;
}

#endif // MYDEQUE_H
