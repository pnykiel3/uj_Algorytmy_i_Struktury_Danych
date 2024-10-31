#include <iostream>
#include "arraylist.h"

void test() {
    ArrayList<int> L1(5);

    std::cout << "Test 1: Stworzono nową liste. Jaką ma pojemność?\n(5) = " << L1.max_size() << std::endl;

    L1.push_back(0);
    L1.push_back(1);
    L1.push_back(8);
    L1.push_back(3);
    L1.push_back(4);

    std::cout << "Test 2: Czy dziala push_back()?\n(0, 1, 8, 3, 4) = ";
    L1.display();

    std::cout << "Test 3: Czy lista jest pełna?\n(1) = " << L1.full() << std::endl;

    std::cout << "Test 4: Pełna lista - dodaj 3 elementy do przodu - push_front()\n(5, 12, 44, 0, 1, 8, 3, 4) = ";
    L1.push_front(44);
    L1.push_front(12);
    L1.push_front(5);
    L1.display();

    std::cout << "Test 5: Ile jest elementów w liście?\n(8) = " << L1.size() << std::endl;

    std::cout << "Test 6: Dodaj element na koniec - push_back()\n(5, 12, 44, 0, 1, 8, 3, 4, 6) = ";
    L1.push_back(6);
    L1.display();

    std::cout << "Test 7: Pierwszy element?\n(5) = " << L1.front() << std::endl;
    std::cout << "Test 8: Ostatni element?\n(6) = " << L1.back() << std::endl;

    std::cout << "Test 9: pop - usuń pierwszy i ostatni element\n(12, 44, 0, 1, 8, 3, 4) = ";
    L1.pop_front();
    L1.pop_back();
    L1.display();

    std::cout << "Test 10: Odwróć listę\n(4, 3, 8, 1, 0, 44, 12) = ";
    L1.reverse();
    L1.display();

    std::cout << "Test 11: Posortuj listę\n(0, 1, 3, 4, 8, 12, 44) = ";
    L1.sort();
    L1.display();

    std::cout << "Test 12: Usuń trzeci element\n(0, 1, 4, 8, 12, 44) = ";
    L1.erase(2);
    L1.display();

    std::cout << "Test 13: Na jakiej pozycji jest \"4\"\n(2) = " << L1.index(4) << std::endl;

    std::cout << "Test 14: Konstruktor kopiujący L2 = L1?\n(0, 1, 4, 8, 12, 44) = ";
    ArrayList<int> L2 = L1;
    L2.display();

    std::cout << "Test 15: Wyczyść listę L2\n() = ";
    L2.clear();
    L2.display();
}

int main() {
    test();
    return 0;
}