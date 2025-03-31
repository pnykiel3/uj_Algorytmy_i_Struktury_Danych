#include <iostream>
#include <cstdlib>
#include "priorityQueueBinary.h"

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

    // Test insert()
    heap.insert(0);
    std::cout << "\nKopiec po wstawieniu 0:" << std::endl;
    heap.printHeap();

    // Test size() i is_empty()
    std::cout << "\nRozmiar kopca: " << heap.size() << std::endl;
    std::cout << "Czy kopiec jest pusty? " << (heap.is_empty() ? "Tak" : "Nie") << std::endl;

    // Usuwanie elementów z kopca
    std::cout << "\nUsuwam elementy z kopca:" << std::endl;
    while(!heap.is_empty()) {
        int minVal = heap.del_min();
        std::cout << "Usunięto: " << minVal << " | Stan kopca: ";
        heap.printHeap();
    }

}

int main() {
    Btest();
    return 0;
}