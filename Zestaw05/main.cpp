#include <iostream>
#include "doublelist.h"

void test() {
    DoubleList<int> L1;

    std::cout << "Test 0: Stworzono nową listę. Czy jest pusta?\n(1) = " << L1.empty() << std::endl;

    L1.push_back(0);
    L1.push_back(1);
    L1.push_back(8);
    L1.push_back(3);
    L1.push_back(4);

    std::cout << "Test 1: Czy działa push_back()?\n(0, 1, 8, 3, 4) = ";
    L1.display();

    std::cout << "Test 2: Ile jest elementów w liście?\n(5) = " << L1.size() << std::endl;

    L1.push_front(44);
    L1.push_front(12);
    L1.push_front(5);

    std::cout << "Test 3: Czy działa push_front()?\n(5, 12, 44, 0, 1, 8, 3, 4) = ";
    L1.display();

    std::cout << "Test 4: Pierwszy element?\n(5) = " << L1.front() << std::endl;
    std::cout << "Test 5: Ostatni element?\n(4) = " << L1.back() << std::endl;

    L1.pop_front();
    L1.pop_back();

    std::cout << "Test 6: Czy działa pop_front() i pop_back()?\n(12, 44, 0, 1, 8, 3) = ";
    L1.display();

    std::cout << "Test 7: Odwrócona kolejność wyświetlania listy\n(3, 8, 1, 0, 44, 12) = ";
    L1.display_reversed();

    DoubleList<int> L2 = L1;
    std::cout << "Test 8: Konstruktor kopiujący L2 = L1?\n(12, 44, 0, 1, 8, 3) = ";
    L2.display();

    L2.clear();
    std::cout << "Test 9: Wyczyść listę L2\n() = ";
    L2.display();

    std::cout << "Test 10: Ile elementów w L2 po wyczyszczeniu?\n(0) = " << L2.size() << std::endl;

    // Nowe testy:
    L2 = L1;
    std::cout << "Test 11: Operator przypisania L2 = L1\n(12, 44, 0, 1, 8, 3) = ";
    L2.display();

    std::cout << "Test 12: Ile elementów w L2 po przypisaniu?\n(6) = " << L2.size() << std::endl;

    L1.clear();
    std::cout << "Test 13: Wyczyść listę L1\n() = ";
    L1.display();

    std::cout << "Test 14: Czy lista L1 jest teraz pusta?\n(1) = " << L1.empty() << std::endl;

    L1.push_back(42);
    std::cout << "Test 15: Dodano 42 na końcu do L1\n(42) = ";
    L1.display();

    L1.push_front(99);
    std::cout << "Test 16: Dodano 99 na początku do L1\n(99, 42) = ";
    L1.display();

    L1.pop_back();
    std::cout << "Test 17: Usunięto ostatni element z L1\n(99) = ";
    L1.display();

    L1.pop_front();
    std::cout << "Test 18: Usunięto pierwszy element z L1\n() = ";
    L1.display();

    std::cout << "Test 19: Ile elementów w L1 po wszystkich operacjach?\n(0) = " << L1.size() << std::endl;
}

int main() {
    test();
    return 0;
}
