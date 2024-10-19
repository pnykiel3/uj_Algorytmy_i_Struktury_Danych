// arraylist.h

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
class ArrayList {
    T* tab;
    int msize; // najwieksza mozliwa liczba elementow
    int last; // pierwsza wolna pozycja
    constexpr static int MIN_SIZE = 2;

    void chopArray() {
        msize--;
        T* newtab = new T[msize];
        for (int i=0; i < last; i++) {
            newtab[i] = tab[i];
        }
        delete [] tab;
        tab = newtab;
    }

    void extendArray() {
        msize++;
        T* newtab = new T[msize];
        for (int i = 0; i < last; i++) {
            newtab[i] = tab[i];
        }
        delete[] tab;
        tab = newtab;
    }
public:

    explicit ArrayList(int s=MIN_SIZE) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    }

    ~ArrayList() { delete [] tab; }
    bool empty() const { return last == 0; } // checks if the container has no elements
    bool full() const { return last == msize; } // checks if the container is full
    int size() const { return last; } // liczba elementow na liscie
    int max_size() const { return msize; } // najwieksza mozliwa liczba elementow

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (int i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        return os;
    }

    void push_front(const T& item) {
    if (full()) extendArray(); 
    for (int i = last; i > 0; --i) {  
        tab[i] = tab[i-1];
    }
    tab[0] = item; 
    last++;  
}

    void push_back(const T& item) {
        if (full()) extendArray();
        tab[last] = item;
        last++;
    }

    T& front() {
        assert( !empty() );
        return tab[0];
    }

    T& back() {
        assert( !empty() );
        return tab[last-1];
    }

    void pop_front() {
        assert(!empty());
        for (int i = 0; i < last - 1; i++) {
            tab[i] = tab[i + 1];
        }
        last--;
    }

    void pop_back() {
        assert(!empty());
        last--;
    }


    void clear() {
        last = 0;
    }


    void display(int s = -1) { //ta metoda w zależności od argumentu wyświetli całą listę(błedny argument, brak argumentu) lub tylko element s
        if (s >= 0 && s < last) {
            std::cout << tab[s] << std::endl;
        } else {
            for (int i = 0; i < last; i++) {
                std::cout << tab[i] << " ";
            }
            std::cout << std::endl;
        }
    }


    void reverse() {
        for (int i = 0; i < last / 2; i++) {
            std::swap(tab[i], tab[last - i - 1]);
        }
    }


    void sort() {
        for (int i=0; i < last; i++) {
            for (int j=0; j < last-1; j++) {
                if (tab[j] > tab[j+1]) {
                    T temp = tab[j];
                    tab[j] = tab[j+1];
                    tab[j+1] = temp;
                }
            }
        }
    }

    void erase(int pos) {
        assert(pos >= 0 && pos < last);
        for (int i = pos; i < last - 1; i++) {
            tab[i] = tab[i + 1];
        }
        last--;
    }

    int index(const T& item) {
        for (int i = 0; i < last; i++) {
            if (tab[i] == item) return i;
        }
        return -1;
    }


    ArrayList(const ArrayList& other) : msize(other.msize), last(other.last) {
        tab = new T[msize];
        for (int i=0; i < last; i++) {
            tab[i] = other.tab[i];
        }
    }

    ArrayList& operator=(const ArrayList& other) {
        if (this == &other) return *this;
        delete [] tab;
        msize = other.msize;
        last = other.last;
        tab = new T[msize];
        for (int i=0; i < last; i++) {
            tab[i] = other.tab[i];
        }
        return *this;
    }

};

#endif

// EOF
