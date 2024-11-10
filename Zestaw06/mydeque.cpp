#include <iostream>
#include "mydeque.h"
#include <cassert>

template <typename T>
void MyDeque<T>::push_front(const T& item) {
    assert(!full());
    head = (head + msize -1) % msize;
    tab[head] = item;
}

template <typename T>
void MyDeque<T>::push_back(const T& item) {
    assert(!full());
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::display() {
    for (std::size_t i = head; i != tail; i=(i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
T& MyDeque<T>::front() {
    return tab[head];
}

template <typename T>
T& MyDeque<T>::back() {
    return tab[(tail + msize -1) % msize];
}

template <typename T>
std::size_t MyDeque<T>::max_size() const {
    return msize-1;
}

template <typename T>
std::size_t MyDeque<T>::size() const {
    return (tail - head + msize) % msize;
}

template <typename T>
bool MyDeque<T>::full() const {
    return (tail + 1) % msize == head;
}

template <typename T>
bool MyDeque<T>::empty() const {
    return head == tail;
}

template <typename T>
void MyDeque<T>::pop_front() {
    assert(!empty());
    tab[head] = nullptr;
    head = (head + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_back() {
    assert(!empty());
    tab[tail - 1] = nullptr;
    tail = (tail - 1) % msize;
}

template <typename T>
void MyDeque<T>::clear() {
    for(int i = 0; i < msize; i++) {
        tab[i] = nullptr;
    }
}

template <typename T>
void MyDeque<T>::display_reversed() {
    for (std::size_t i = (tail + msize - 1) % msize; i != head; i = (i + msize - 1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << tab[head] << std::endl;
}

template <typename T>
MyDeque<T>::MyDeque(const MyDeque& other) : msize(other.msize), head(other.head), tail(other.tail) {
    tab = new T[msize];
    for (std::size_t i = 0; i < msize; ++i) {
        tab[i] = other.tab[i];
    }
}

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
MyDeque<T>::~MyDeque() {
    delete[] tab;
}