#include <iostream>
#include <cassert>
#include "mystack.h"

void test() {
    MyStack<int> S1;

    // Test 0: Czy nowy stos jest pusty?
    assert(S1.empty());
    assert(S1.size() == 0);

    // Test 1: Dodajemy elementy na stos (push)
    S1.push(10);
    S1.push(20);
    S1.push(30);
    assert(!S1.empty());
    assert(S1.size() == 3);
    assert(S1.top() == 30); // Ostatni element

    // Test 2: Usuwanie elementów (pop)
    S1.pop();
    assert(S1.size() == 2);
    assert(S1.top() == 20); // Ostatni element po usunięciu

    S1.pop();
    assert(S1.size() == 1);
    assert(S1.top() == 10); // Ostatni element po usunięciu

    S1.pop();
    assert(S1.empty());
    assert(S1.size() == 0);

    // Test 3: Dodawanie elementów ponownie
    S1.push(42);
    assert(S1.size() == 1);
    assert(S1.top() == 42);

    S1.push(100);
    assert(S1.size() == 2);
    assert(S1.top() == 100);

    // Test 4: Sprawdzenie kopiowania (konstruktor kopiujący)
    MyStack<int> S2 = S1; // Kopiowanie
    assert(S2.size() == 2);
    assert(S2.top() == 100);

    S2.pop();
    assert(S2.size() == 1);
    assert(S2.top() == 42);

    // Test 5: Sprawdzenie przenoszenia (konstruktor przenoszący)
    MyStack<int> S3 = std::move(S2); // Przenoszenie
    assert(S3.size() == 1);
    assert(S3.top() == 42);
    assert(S2.empty()); // S2 powinien być pusty po przeniesieniu

    // Test 6: Sprawdzenie operatora przypisania kopiującego
    S2 = S1;
    assert(S2.size() == 2);
    assert(S2.top() == 100);

    // Test 7: Sprawdzenie operatora przypisania przenoszącego
    S2 = std::move(S3);
    assert(S2.size() == 1);
    assert(S2.top() == 42);
    assert(S3.empty()); // S3 powinien być pusty po przeniesieniu

    // Test 8: Sprawdzenie wyczyszczenia stosu
    S1.clear();
    assert(S1.empty());
    assert(S1.size() == 0);

    std::cout << "Wszystkie testy zakończone pomyślnie!" << std::endl;
}

int main() {
    test();
    return 0;
}
