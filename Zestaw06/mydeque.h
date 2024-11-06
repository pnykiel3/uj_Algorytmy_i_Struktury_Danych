
#include <iostream>
// mydeque.h


template <typename T>
class MyDeque {
    T* tab;
    std::size_t msize; // największa możliwa liczba elementów plus jeden
    std::size_t head; // pierwszy do pobrania
    std::size_t tail; // pierwsza wolna pozycja
public:
    MyDeque(std::size_t s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    } // default constructor
    ~MyDeque() { delete [] tab; }
    MyDeque(const MyDeque& other); // copy constructor
    MyDeque(MyDeque&& other); // move constructor NIEOBOWIĄZKOWE
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    MyDeque& operator=(const MyDeque& other); // copy assignment operator, return *this
    MyDeque& operator=(MyDeque&& other); // move assignment operator, return *this NIEOBOWIĄZKOWE
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    bool empty() const { return head == tail; }
    bool full() const { return (tail + 1) % msize == head; }
    std::size_t size() const { return (tail - head + msize) % msize; }
    std::size_t max_size() const { return msize-1; }
    void push_front(const T& item); // dodanie na początek O(1)
    void push_front(T&& item); // dodanie na początek O(1) NIEOBOWIĄZKOWE
    void push_back(const T& item); // dodanie na koniec O(1)
    void push_back(T&& item); // dodanie na koniec O(1) NIEOBOWIĄZKOWE
    T& front() { return tab[head]; } // zwraca poczatek
    T& back() { return tab[(tail + msize -1) % msize]; } // zwraca koniec
    void pop_front(); // usuwa początek kolejki O(1)
    void pop_back(); // usuwa koniec kolejki O(1)
    void clear(); // czyszczenie listy z elementów
    void display();
    void display_reversed();
    // Operacje z indeksami. NIEOBOWIĄZKOWE
    T& operator[](std::size_t pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](std::size_t pos) const; // dostęp do obiektu const
    void erase(std::size_t pos);
    int index(const T& item); // jaki index na liście (-1 gdy nie ma)
    void insert(std::size_t pos, const T& item); // inserts item before pos
    void insert(std::size_t pos, T&& item); // inserts item before pos
};
