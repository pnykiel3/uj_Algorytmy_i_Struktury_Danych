#include <iostream>
#include "mydeque.h"

void test() {
    MyDeque<int> D1;

    std::cout << "Test 0: Stworzono nową kolejkę. Czy jest pusta?\n(1) = " << D1.empty() << std::endl;

    D1.push_back(0);
    D1.push_back(1);
    D1.push_back(8);
    D1.push_back(3);
    D1.push_back(4);

    std::cout << "Test 1: Czy działa push_back()?\n(0, 1, 8, 3, 4) = ";
    D1.display();

    std::cout << "Test 2: Ile jest elementów w kolejce?\n(5) = " << D1.size() << std::endl;

    D1.push_front(44);
    D1.push_front(12);
    D1.push_front(5);

    std::cout << "Test 3: Czy działa push_front()?\n(5, 12, 44, 0, 1, 8, 3, 4) = ";
    D1.display();

    std::cout << "Test 4: Pierwszy element?\n(5) = " << D1.front() << std::endl;
    std::cout << "Test 5: Ostatni element?\n(4) = " << D1.back() << std::endl;

    D1.pop_front();
    D1.pop_back();

    std::cout << "Test 6: Czy działa pop_front() i pop_back()?\n(12, 44, 0, 1, 8, 3) = ";
    D1.display();

    std::cout << "Test 7: Odwrócona kolejność wyświetlania kolejki\n(3, 8, 1, 0, 44, 12) = ";
    D1.display_reversed();

    MyDeque<int> D2 = D1;
    std::cout << "Test 8: Konstruktor kopiujący D2 = D1?\n(12, 44, 0, 1, 8, 3) = ";
    D2.display();

    D2.clear();
    std::cout << "Test 9: Wyczyść kolejkę D2\n() = ";
    D2.display();

    std::cout << "Test 10: Ile elementów w D2 po wyczyszczeniu?\n(0) = " << D2.size() << std::endl;

    // Nowe testy:
    D2 = D1;
    std::cout << "Test 11: Operator przypisania D2 = D1\n(12, 44, 0, 1, 8, 3) = ";
    D2.display();

    std::cout << "Test 12: Ile elementów w D2 po przypisaniu?\n(6) = " << D2.size() << std::endl;

    D1.clear();
    std::cout << "Test 13: Wyczyść kolejkę D1\n() = ";
    D1.display();

    std::cout << "Test 14: Czy kolejka D1 jest teraz pusta?\n(1) = " << D1.empty() << std::endl;

    D1.push_back(42);
    std::cout << "Test 15: Dodano 42 na końcu do D1\n(42) = ";
    D1.display();

    D1.push_front(99);
    std::cout << "Test 16: Dodano 99 na początku do D1\n(99, 42) = ";
    D1.display();

    D1.pop_back();
    std::cout << "Test 17: Usunięto ostatni element z D1\n(99) = ";
    D1.display();

    D1.pop_front();
    std::cout << "Test 18: Usunięto pierwszy element z D1\n() = ";
    D1.display();

    std::cout << "Test 19: Ile elementów w D1 po wszystkich operacjach?\n(0) = " << D1.size() << std::endl;
}

int main() {
    test();
    return 0;
}

