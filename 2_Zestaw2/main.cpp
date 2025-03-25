//
// Created by pawelubuntu on 3/18/25.
//
#include <cassert>
#include "setHashed.h"


void TestSetHashed() {

    // Test 1: Wstawianie i sprawdzanie obecności elementów
    SetHashed<int> set1;
    assert(set1.insert(10) == true);  // Wstawienie 10
    assert(set1.insert(20) == true);  // Wstawienie 20
    assert(set1.insert(10) == false); // Ponowne wstawienie 10 (powinno zwrócić false)
    assert(set1.contains(10) == true); // Sprawdzenie, czy 10 jest w zbiorze
    assert(set1.contains(20) == true); // Sprawdzenie, czy 20 jest w zbiorze
    assert(set1.contains(30) == false); // Sprawdzenie, czy 30 nie jest w zbiorze

    // Test 2: Usuwanie elementów
    assert(set1.remove(10) == true);  // Usunięcie 10
    assert(set1.contains(10) == false); // Sprawdzenie, czy 10 został usunięty
    assert(set1.remove(30) == false); // Próba usunięcia nieistniejącego elementu (powinno zwrócić false)

    // Test 3: Suma zbiorów
    SetHashed<int> set2;
    set2.insert(20);
    set2.insert(30);

    SetHashed<int> sumSet = set1.sum(set2);
    assert(sumSet.contains(20) == true); // 20 jest w obu zbiorach
    assert(sumSet.contains(30) == true); // 30 jest w set2
    assert(sumSet.contains(10) == false); // 10 nie jest w sumie, bo został usunięty z set1

    // Test 4: Część wspólna zbiorów
    SetHashed<int> intersectionSet = set1.intersection(set2);
    assert(intersectionSet.contains(20) == true); // 20 jest w obu zbiorach
    assert(intersectionSet.contains(30) == false); // 30 nie jest w set1
    assert(intersectionSet.contains(10) == false); // 10 nie jest w set1

    // Test 5: Różnica zbiorów
    SetHashed<int> differenceSet = set1.difference(set2);
    assert(differenceSet.contains(20) == false); // 20 jest w obu zbiorach
    assert(differenceSet.contains(30) == false); // 30 nie jest w set1
    assert(differenceSet.contains(10) == false); // 10 nie jest w set1

    // Test 6: Równość zbiorów
    SetHashed<int> set3;
    set3.insert(20);
    assert(set1.equals(set3) == true); // set1 i set3 zawierają tylko 20
    set3.insert(40);
    assert(set1.equals(set3) == false); // set3 zawiera dodatkowo 40

    // Test 7: Pusty zbiór
    SetHashed<int> emptySet;
    assert(emptySet.contains(10) == false); // Pusty zbiór nie zawiera elementów
    assert(emptySet.remove(10) == false); // Próba usunięcia z pustego zbioru

    // Test 8: Wstawianie wielu elementów
    SetHashed<int> largeSet;
    for (int i = 0; i < 100; ++i) {
        assert(largeSet.insert(i) == true); // Wstawianie kolejnych liczb
    }
    for (int i = 0; i < 100; ++i) {
        assert(largeSet.contains(i) == true); // Sprawdzenie, czy liczby są w zbiorze
    }

    std::cout << "Test setHashed zakończony pomyślnie!"  << std::endl;
}

int main() {
    TestSetHashed();
    std::cout << "Wszystkie testy zakończone pomyślnie!" << std::endl;
    return 0;
}
