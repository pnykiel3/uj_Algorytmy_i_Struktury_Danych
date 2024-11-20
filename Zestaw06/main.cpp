
#include <iostream>
#include <cassert>
#include "mydeque.h"

void test() {
    MyDeque<int> D1;

    // Test 0: Czy nowa kolejka jest pusta?
    assert(D1.empty());

    // Test 1: Test push_back
    D1.push_back(0);
    D1.push_back(1);
    D1.push_back(8);
    D1.push_back(3);
    D1.push_back(4);
    assert(D1.size() == 5);

    // Test 2: Test push_front
    D1.push_front(44);
    D1.push_front(12);
    D1.push_front(5);
    assert(D1.size() == 8);
    assert(D1.front() == 5);
    assert(D1.back() == 4);

    // Test 3: Test pop_front and pop_back
    D1.pop_front();
    D1.pop_back();
    assert(D1.size() == 6);
    assert(D1.front() == 12);
    assert(D1.back() == 3);

    // Test 4: Test display and display_reversed manually
    std::cout << "Expected order (normal): 12 44 0 1 8 3" << std::endl;
    std::cout << "Actual order (normal): ";
    D1.display();
    
    std::cout << "Expected order (reversed): 3 8 1 0 44 12" << std::endl;
    std::cout << "Actual order (reversed): ";
    D1.display_reversed();

    // Test 5: Konstruktor kopiujący
    MyDeque<int> D2 = D1;
    assert(D2.size() == D1.size());

    // Test 6: Clear queue
    D2.clear();
    assert(D2.empty());
    assert(D2.size() == 0);

    // Test 7: Operator przypisania
    D2 = D1;
    assert(D2.size() == D1.size());

    // Test 8: Clear and empty check
    D1.clear();
    assert(D1.empty());

    // Test 9: Ponowne dodawanie elementów i sprawdzenie front i back
    D1.push_back(42);
    assert(D1.size() == 1);
    assert(D1.front() == 42);

    D1.push_front(99);
    assert(D1.size() == 2);
    assert(D1.front() == 99);
    assert(D1.back() == 42);

    // Test 10: pop_back i pop_front
    D1.pop_back();
    assert(D1.size() == 1);
    assert(D1.front() == 99);

    D1.pop_front();
    assert(D1.empty());
    assert(D1.size() == 0);

    std::cout << "Wszystkie testy zakończone pomyślnie!" << std::endl;
}

int main() {
    test();
    return 0;
}

