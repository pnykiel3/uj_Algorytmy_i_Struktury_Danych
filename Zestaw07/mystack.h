#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <vector>
#include <utility> // for std::move

// Interfejs stosu na bazie kontenera std::vector.
template <typename T>
class MyStack {
    std::vector<T> lst;

public:
    MyStack(std::size_t s = 10) {
        lst.reserve(s);
    } // default constructor

    ~MyStack() {
        lst.clear();
    }

    // Konstruktor kopiujący
    MyStack(const MyStack& other) {
        lst = other.lst;
    }

    // Konstruktor przenoszący
    MyStack(MyStack&& other) noexcept {
        lst = std::move(other.lst);
    }

    // Operator przypisania kopiującego
    MyStack& operator=(const MyStack& other) {
        if (this != &other) {
            lst = other.lst;
        }
        return *this;
    }

    // Operator przypisania przenoszącego
    MyStack& operator=(MyStack&& other) noexcept {
        if (this != &other) {
            lst = std::move(other.lst);
        }
        return *this;
    }

    bool empty() const {
        return lst.empty();
    } // checks if the container has no elements

    bool full() const {
        return lst.size() == lst.capacity();
    }

    std::size_t size() const {
        return lst.size();
    }

    std::size_t max_size() const {
        return lst.capacity();
    }

    void push(const T& item) {
        lst.push_back(item);
    }

    void push(T&& item) {
        lst.push_back(std::move(item));
    }

    T& top() {
        return lst.back();
    } // zwraca koniec, nie usuwa

    void pop() {
        lst.pop_back();
    } // usuwa koniec

    void clear() {
        lst.clear();
    }

    void display() {
        for (const auto& item : lst) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

#endif // MYSTACK_H
