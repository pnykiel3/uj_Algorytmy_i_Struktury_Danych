#include <iostream>
#include "setsimple.h"
#include "dictionarysimple.h"
#include "setlinked.h"
#include <cassert>

void testSetSimple() {
    std::cout << "=== Testowanie setSimple ===" << std::endl;
    setSimple set1 = setSimple(10);
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    assert(set1.exists(1));
    assert(set1.exists(2));
    assert(set1.exists(3));

    std::cout << "Zbiór set1: " << std::endl;
    set1.print();

    setSimple set2 = setSimple(10);
    set2.insert(3);
    set2.insert(4);
    set2.insert(5);
    assert(set2.exists(3));
    assert(set2.exists(4));
    assert(set2.exists(5));

    std::cout << "Zbiór set2: " << std::endl;
    set2.print();

    setSimple setSum = set1.sum(set2);
    std::cout << "Suma set1 i set2: " << std::endl;
    setSum.print();
    assert(setSum.exists(1));
    assert(setSum.exists(2));
    assert(setSum.exists(3));
    assert(setSum.exists(4));
    assert(setSum.exists(5));

    setSimple setIntersection = set1.intersection(set2);
    std::cout << "Część wspólna set1 i set2: " << std::endl;
    setIntersection.print();
    assert(setIntersection.exists(3));
    assert(!setIntersection.exists(1));
    assert(!setIntersection.exists(2));
    assert(!setIntersection.exists(4));
    assert(!setIntersection.exists(5));

    setSimple setComplement = set1.complement(set2);
    std::cout << "Różnica set1 - set2: " << std::endl;
    setComplement.print();
    assert(setComplement.exists(1));
    assert(setComplement.exists(2));
    assert(!setComplement.exists(3));
    assert(!setComplement.exists(4));
    assert(!setComplement.exists(5));

    std::cout << "Czy set1 równa się set2? " << (set1.equals(set2) ? "Tak" : "Nie") << std::endl;
    assert(!set1.equals(set2));

    set1.remove(2);
    std::cout << "set1 po usunięciu elementu 2: " << std::endl;
    set1.print();
    assert(!set1.exists(2));

    std::cout << std::endl;
}


void testDictionarySimple() {
    std::cout << "=== Testowanie dictionarysimple ===" << std::endl;
    dictionarysimple dict1;
    dict1.insert("apple");
    dict1.insert("banana");
    dict1.insert("cherry");
    assert(dict1.exists("apple"));
    assert(dict1.exists("banana"));
    assert(dict1.exists("cherry"));

    std::cout << "Zbiór dict1: " << std::endl;
    dict1.print();

    dictionarysimple dict2;
    dict2.insert("banana");
    dict2.insert("date");
    dict2.insert("elderberry");
    assert(dict2.exists("banana"));
    assert(dict2.exists("date"));
    assert(dict2.exists("elderberry"));

    std::cout << "Zbiór dict2: " << std::endl;
    dict2.print();

    dict1.remove("banana");
    std::cout << "dict1 po usunięciu 'banana': " << std::endl;
    dict1.print();
    assert(!dict1.exists("banana"));

    std::cout << "Czy 'cherry' istnieje w dict1? " << (dict1.exists("cherry") ? "Tak" : "Nie") << std::endl;
    std::cout << "Czy 'banana' istnieje w dict1? " << (dict1.exists("banana") ? "Tak" : "Nie") << std::endl;

    std::cout << std::endl;
}

void testSetLinked() {
    std::cout << "=== Testowanie setLinked ===" << std::endl;
    setLinked set1;
    set1.insert(10);
    set1.insert(30);
	set1.insert(20);
    assert(set1.exists(10));
    assert(set1.exists(20));
    assert(set1.exists(30));

    std::cout << "Zbiór set1: ";
    set1.print();

    setLinked set2;
    set2.insert(50);
    set2.insert(40);
    set2.insert(30);
	assert(set2.exists(30));
    assert(set2.exists(40));
    assert(set2.exists(50));

    std::cout << "Zbiór set2: ";
    set2.print();

    setLinked setSum = set1.sum(set2);
    std::cout << "Suma set1 i set2: ";
    setSum.print();
    assert(setSum.exists(10));
    assert(setSum.exists(20));
    assert(setSum.exists(30));
    assert(setSum.exists(40));
    assert(setSum.exists(50));

    setLinked setIntersection = set1.intersection(set2);
    std::cout << "Część wspólna set1 i set2: ";
    setIntersection.print();
    assert(setIntersection.exists(30));
    assert(!setIntersection.exists(10));
    assert(!setIntersection.exists(20));
    assert(!setIntersection.exists(40));
    assert(!setIntersection.exists(50));

    setLinked setComplement = set1.complement(set2);
    std::cout << "Różnica set1 - set2: ";
    setComplement.print();
    assert(setComplement.exists(10));
    assert(setComplement.exists(20));
    assert(!setComplement.exists(30));
    assert(!setComplement.exists(40));
    assert(!setComplement.exists(50));


    std::cout << "Czy set1 równa się set2? " << (set1.equals(set2) ? "Tak" : "Nie") << std::endl;
    assert(!set1.equals(set2));

    set1.remove(20);
    std::cout << "set1 po usunięciu 20: ";
    set1.print();
    assert(!set1.exists(20));

    std::cout << std::endl;
}

int main() {
    testSetSimple();
    testDictionarySimple();
    testSetLinked();
    std::cout << "Wszystkie testy zakończone pomyślnie." << std::endl;

    return 0;
}