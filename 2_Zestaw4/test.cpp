//
// Created by Paweł Nykiel on 20/04/2025.
//

#include <cassert>
#include <iostream>
#include <vector>    // Potrzebne do porównania sąsiadów
#include <algorithm> // Potrzebne do sortowania sąsiadów
#include "ADTgraph.h"

// Nie definiujemy już statycznej pojemności, klasa zarządza nią dynamicznie

// --- Testy Operacji na Wierzchołkach ---
void testVertexOperations() {
    ADTgraph<10> g; // Tworzymy graf o pojemności 10

    // Test dodawania wierzchołków
    g.addVertex(1);
    assert(g.getVertexValue(1) == 1); // Sprawdź, czy wierzchołek istnieje
    g.addVertex(3);
    assert(g.getVertexValue(3) == 1);
    g.addVertex(5);
    assert(g.getVertexValue(5) == 1);
    assert(g.getSize() == 3); // Sprawdź rozmiar grafu

    // Test ustawiania wartości wierzchołka
    g.setVertexValue(3, 42);
    assert(g.getVertexValue(3) == 42); // Sprawdź, czy wartość została zmieniona

    // Test usuwania wierzchołka
    g.removeVertex(3);
    assert(g.getVertexValue(3) == 0); // Sprawdź, czy wierzchołek został usunięty
    assert(g.getSize() == 2); // Sprawdź, czy rozmiar się zmniejszył

    std::cout << "Testy operacji na wierzchołkach zakończone pomyślnie.\n";
}

// --- Testy Operacji na Krawędziach ---
void testEdgeOperations() {
    ADTgraph<10> g;

    // Najpierw dodaj wierzchołki
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);

    // Test dodawania krawędzi (używa domyślnej wartości 1)
    g.addEdge(1, 2);
    assert(g.getEdgeValue(1, 2) == 1); // Sprawdź, czy krawędź istnieje

    // Test ustawiania wartości krawędzi
    g.setEdgeValue(1, 2, 55);
    assert(g.getEdgeValue(1, 2) == 55); // Sprawdź, czy wartość krawędzi została zmieniona
    g.setEdgeValue(2, 3, 99); // Ustaw inną krawędź
    assert(g.getEdgeValue(2, 3) == 99);

    // Test ustawiania wartości krawędzi, gdy wierzchołek nie istnieje (nie powinno nic zmienić)
    g.setEdgeValue(1, 4, 100);
    assert(g.getEdgeValue(1, 4) == 0);

    // Test usuwania krawędzi
    g.removeEdge(1, 2);
    assert(g.getEdgeValue(1, 2) == 0); // Sprawdź, czy krawędź została usunięta

    std::cout << "Testy operacji na krawędziach zakończone pomyślnie.\n";
}

// --- Testy Sąsiedztwa ---
void testAdjacency() {
    ADTgraph<10> g;

    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);

    g.setEdgeValue(1, 2, 1); // Dodaj krawędź 1 -> 2
    g.setEdgeValue(1, 3, 5); // Dodaj krawędź 1 -> 3

    // Sprawdź sąsiedztwo
    assert(g.adjacent(1, 2) == true);  // Powinny być sąsiadami
    assert(g.adjacent(1, 3) == true);  // Powinny być sąsiadami
    assert(g.adjacent(2, 1) == false); // Graf skierowany, brak krawędzi 2 -> 1
    assert(g.adjacent(2, 3) == false); // Brak krawędzi 2 -> 3

    // Sprawdź sąsiedztwo po usunięciu krawędzi
    g.removeEdge(1, 2);
    assert(g.adjacent(1, 2) == false); // Już nie są sąsiadami

    std::cout << "Testy sąsiedztwa zakończone pomyślnie.\n";
}

// --- Testy Pobierania Sąsiadów ---
void testNeighbors() {
    ADTgraph<10> g;

    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);

    g.setEdgeValue(1, 2, 1); // Krawędź 1 -> 2
    g.setEdgeValue(1, 3, 1); // Krawędź 1 -> 3
    g.setEdgeValue(1, 4, 1); // Krawędź 1 -> 4

    int* neighbors_ptr = g.neighbors(1); // Pobierz sąsiadów wierzchołka 1

    // Sprawdź, czy znaleziono oczekiwanych sąsiadów (kolejność nie jest gwarantowana)
    std::vector<int> actual_neighbors;
    for (int i = 0; neighbors_ptr[i] != 0; ++i) { // Pętla do znaku końca (0)
        actual_neighbors.push_back(neighbors_ptr[i]);
    }
    std::sort(actual_neighbors.begin(), actual_neighbors.end()); // Posortuj dla łatwiejszego porównania

    std::vector<int> expected_neighbors = {2, 3, 4};
    assert(actual_neighbors == expected_neighbors); // Porównaj z oczekiwaną listą

    delete[] neighbors_ptr; // WAŻNE: Zwolnij pamięć zaalokowaną przez funkcję neighbors!

    // Sprawdź sąsiadów dla wierzchołka bez wychodzących krawędzi
    neighbors_ptr = g.neighbors(2);
    assert(neighbors_ptr[0] == 0); // Pierwszy element powinien być 0 (brak sąsiadów)
    delete[] neighbors_ptr; // Zwolnij pamięć

    std::cout << "Testy pobierania sąsiadów zakończone pomyślnie.\n";
}

// --- Testy Metody getSize() ---
void testSizeMethod() {
    ADTgraph<10> g;

    // Początkowy rozmiar
    assert(g.getSize() == 0);

    // Dodaj wierzchołki i sprawdzaj rozmiar
    g.addVertex(1);
    assert(g.getSize() == 1);
    g.addVertex(5);
    assert(g.getSize() == 2);
    g.addVertex(9);
    assert(g.getSize() == 3);

    // Usuń wierzchołek i sprawdź rozmiar
    g.removeVertex(5);
    assert(g.getSize() == 2);

    // Usuń ostatnie wierzchołki
    g.removeVertex(1);
    g.removeVertex(9);
    assert(g.getSize() == 0);

    std::cout << "Testy metody getSize() zakończone pomyślnie.\n";
}

// --- Główna Funkcja Testująca ---
int main() {
    std::cout << "Rozpoczynanie testów ADTgraph...\n";

    // Wywołaj poszczególne funkcje testujące
    testVertexOperations();
    testEdgeOperations();
    testAdjacency();
    testNeighbors();
    testSizeMethod();

    std::cout << "Wszystkie testy zakończone.\n";
    return 0;
}