#include <iostream>
#include <cstdlib>
#include "priorityQueueBinary.h"
#include "priorityQueue.h"
#include <cassert> // Dodajemy assert do testowania

void Btest() {
    BinaryHeap heap;

    // Przykład: budowanie kopca z podanej tablicy
    int arr[] = {10, 4, 15, 1, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    heap.build_heap(arr, n);

    std::cout << "Kopiec po build_heap:" << std::endl;
    heap.printHeap();

    // Test find_min()
    std::cout << "Najmniejszy element: " << heap.find_min() << std::endl;
    assert(heap.find_min() == 1);

    // Test insert()
    heap.push(0);
    std::cout << "\nKopiec po wstawieniu 0:" << std::endl;
    heap.printHeap();
    assert(heap.find_min() == 0);
    assert(heap.size() == 6);

    // Test size() i is_empty()
    std::cout << "\nRozmiar kopca: " << heap.size() << std::endl;
    std::cout << "Czy kopiec jest pusty? " << (heap.is_empty() ? "Tak" : "Nie") << std::endl;
    assert(!heap.is_empty());
    assert(heap.size() == 6);

    // Usuwanie elementów z kopca
    std::cout << "\nUsuwam elementy z kopca:" << std::endl;
    int expected[] = {0, 1, 4, 7, 10, 15};
    int i = 0;
    while(!heap.is_empty()) {
        int minVal = heap.pop();
        std::cout << "Usunięto: " << minVal << " | Stan kopca: ";
        heap.printHeap();
        assert(minVal == expected[i++]);
    }
    assert(heap.is_empty());
    assert(heap.size() == 0);
}

void testA() {
    priorityQueue<int> pq;

    // Test is_empty() na pustej kolejce
    std::cout << "\nTest kolejki priorytetowej:" << std::endl;
    std::cout << "Czy kolejka jest pusta na początku? " << (pq.size() == 0 ? "Tak" : "Nie") << std::endl;
    assert(pq.size() == 0);

    // Test push()
    pq.push(10, 3);
    pq.push(4, 1);
    pq.push(15, 4);
    pq.push(1, 0);
    pq.push(7, 2);
    std::cout << "Kolejka po wstawieniu elementów (wypisanie nie jest sortowane): ";
    pq.print();
    assert(pq.size() == 5);

    // Test pop() i kolejności
    std::cout << "Usuwanie elementów z kolejki (powinny być w kolejności priorytetów): ";
    assert(pq.pop() == 1);
    std::cout << "Usunięto: 1 | Stan kolejki: "; pq.print();
    assert(pq.pop() == 4);
    std::cout << "Usunięto: 4 | Stan kolejki: "; pq.print();
    assert(pq.pop() == 7);
    std::cout << "Usunięto: 7 | Stan kolejki: "; pq.print();
    assert(pq.pop() == 10);
    std::cout << "Usunięto: 10 | Stan kolejki: "; pq.print();
    assert(pq.pop() == 15);
    std::cout << "Usunięto: 15 | Stan kolejki: "; pq.print();
    assert(pq.size() == 0);

    // Test is_empty() po usunięciu wszystkich elementów
    std::cout << "Czy kolejka jest pusta na końcu? " << (pq.size() == 0 ? "Tak" : "Nie") << std::endl;
    assert(pq.size() == 0);

    // Test push z duplikatem (powinien zostać zignorowany)
    pq.push(5, 2);
    pq.push(5, 1);
    std::cout << "Kolejka po wstawieniu duplikatu 5 (priorytet 2 i 1): "; pq.print();
    assert(pq.size() == 1);
    assert(pq.pop() == 5);
    assert(pq.size() == 0);

    // Test konstruktora z jednym elementem
    priorityQueue<int> pq_single(20, 5);
    std::cout << "Kolejka z jednym elementem: "; pq_single.print();
    assert(pq_single.size() == 1);
    assert(pq_single.pop() == 20);
    assert(pq_single.size() == 0);
}

void testD(){
    BinaryHeap d;
    d.push(1);
    d.push(2);
    d.push(30);
    d.push(4);
    d.push(35);
    d.pop();

}

int main() {
    testD();
    return 0;
}