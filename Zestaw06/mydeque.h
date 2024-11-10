// mydeque.h

#include <iostream>

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
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    MyDeque& operator=(const MyDeque& other); // copy assignment operator, return *this
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
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