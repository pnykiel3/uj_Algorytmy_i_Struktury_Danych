#include "NEIGHBORgraph.h"
#include <cassert>

int main() {
    std::cout << "Rozpoczęcie testów ADTgraph..." << std::endl;

    ADTgraph g;

    // === Testy pustego grafu ===
    std::cout << "Testy pustego grafu..." << std::endl;
    assert(g.size() == 0);
    assert(g.getVertexValue(1) == -1);
    assert(g.getEdgeValue(1, 2) == -1);
    assert(!g.adjacent(1, 2));
    assert(g.neighbors(1).empty());
    assert(g.neighbors(50).empty()); // Test dla dowolnego innego wierzchołka

    // === Testy operacji na wierzchołkach ===
    std::cout << "Testy operacji na wierzchołkach..." << std::endl;
    g.addVertex(10);
    g.addVertex(20);
    g.addVertex(30);
    assert(g.size() == 3);

    g.addVertex(10); // Dodanie istniejącego wierzchołka nie powinno nic zmienić
    assert(g.size() == 3);

    assert(g.getVertexValue(10) == 0); // Domyślna waga = 0
    assert(g.getVertexValue(20) == 0);
    assert(g.getVertexValue(30) == 0);
    assert(g.getVertexValue(40) == -1); // Nieistniejący wierzchołek

    g.setVertexValue(10, 100);
    g.setVertexValue(20, 200);
    assert(g.getVertexValue(10) == 100);
    assert(g.getVertexValue(20) == 200);
    assert(g.getVertexValue(30) == 0); // Nie zmieniony

    g.setVertexValue(40, 400); // Ustawienie wartości dla nieistniejącego wierzchołka
    assert(g.getVertexValue(40) == -1); // Powinno nadal zwracać -1

    // === Testy operacji na krawędziach ===
    std::cout << "Testy operacji na krawędziach..." << std::endl;
    g.addEdge(10, 20);
    g.addEdge(10, 30);
    g.addEdge(20, 30);

    assert(g.adjacent(10, 20));
    assert(g.adjacent(10, 30));
    assert(g.adjacent(20, 30));
    assert(!g.adjacent(30, 10)); // Graf skierowany
    assert(!g.adjacent(20, 10));
    assert(!g.adjacent(10, 10)); // Brak pętli własnej (chyba że dodamy)
    assert(!g.adjacent(10, 40)); // Krawędź do nieistniejącego wierzchołka (nie została dodana)
    assert(!g.adjacent(40, 10)); // Krawędź z nieistniejącego wierzchołka

    g.addEdge(10, 40); // Próba dodania krawędzi do nieistniejącego wierzchołka
    assert(!g.adjacent(10, 40));
    g.addEdge(40, 10); // Próba dodania krawędzi z nieistniejącego wierzchołka
    assert(!g.adjacent(40, 10));

    // Testowanie neighbors (wyniki mogą być w różnej kolejności, sortujemy dla porównania)
    std::list<int> n10 = g.neighbors(10);
    n10.sort();
    assert(n10.size() == 2);
    assert(n10.front() == 20);
    assert(n10.back() == 30);

    std::list<int> n20 = g.neighbors(20);
    n20.sort(); // Chociaż tu jest tylko jeden element
    assert(n20.size() == 1);
    assert(n20.front() == 30);

    std::list<int> n30 = g.neighbors(30);
    assert(n30.empty());

    assert(g.neighbors(40).empty()); // Sąsiedzi nieistniejącego wierzchołka

    // Testy wag krawędzi
    assert(g.getEdgeValue(10, 20) == 0); // Domyślna waga 0
    assert(g.getEdgeValue(10, 30) == 0);
    assert(g.getEdgeValue(20, 30) == 0);
    assert(g.getEdgeValue(30, 10) == -1); // Nieistniejąca krawędź

    g.setEdgeValue(10, 20, 12);
    g.setEdgeValue(10, 30, 13);
    g.setEdgeValue(20, 30, 23);
    assert(g.getEdgeValue(10, 20) == 12);
    assert(g.getEdgeValue(10, 30) == 13);
    assert(g.getEdgeValue(20, 30) == 23);

    g.setEdgeValue(10, 10, 11); // Próba ustawienia wagi nieistniejącej krawędzi
    assert(g.getEdgeValue(10, 10) == -1);
    g.setEdgeValue(40, 10, 41); // Próba ustawienia wagi z nieistniejącego wierzchołka
    assert(g.getEdgeValue(40, 10) == -1);
    g.setEdgeValue(10, 40, 14); // Próba ustawienia wagi do nieistniejącego wierzchołka
    assert(g.getEdgeValue(10, 40) == -1);

    // Testowanie removeEdge
    g.removeEdge(10, 30);
    assert(!g.adjacent(10, 30));
    assert(g.getEdgeValue(10, 30) == -1);
    n10 = g.neighbors(10); // Sprawdź sąsiadów ponownie
    n10.sort();
    assert(n10.size() == 1);
    assert(n10.front() == 20);

    g.removeEdge(10, 30); // Próba usunięcia nieistniejącej krawędzi (nic się nie dzieje)
    assert(!g.adjacent(10, 30));
    assert(n10.size() == 1);

    g.removeEdge(40, 10); // Próba usunięcia z nieistniejącego wierzchołka
    assert(g.size() == 3); // Rozmiar bez zmian

    // === Testy removeVertex ===
    std::cout << "Testy removeVertex..." << std::endl;
    g.addVertex(5); // Dodaj nowy wierzchołek
    g.addEdge(5, 10); // Krawędź wchodząca do 10
    g.addEdge(30, 10); // Druga krawędź wchodząca do 10
    g.addEdge(20, 5);  // Krawędź wychodząca z 20, wchodząca do 5
    assert(g.size() == 4);
    assert(g.adjacent(5, 10));
    assert(g.adjacent(30, 10));
    assert(g.adjacent(20, 5));

    g.removeVertex(10); // Usuwamy wierzchołek 10
    assert(g.size() == 3); // Rozmiar powinien spaść
    assert(g.getVertexValue(10) == -1); // Wierzchołek nie istnieje
    assert(!g.adjacent(10, 20)); // Krawędzie wychodzące z 10 zniknęły
    assert(!g.adjacent(5, 10));  // Krawędź wchodząca 5->10 powinna zniknąć
    assert(!g.adjacent(30, 10)); // Krawędź wchodząca 30->10 powinna zniknąć

    // Sprawdź, czy inne krawędzie pozostały
    assert(g.adjacent(20, 30));
    assert(g.adjacent(20, 5));

    // Sprawdź sąsiadów wierzchołków, których krawędzie wchodziły do 10
    std::list<int> n5 = g.neighbors(5);
    assert(n5.empty()); // Krawędź 5->10 usunięta

    std::list<int> n30_after_remove = g.neighbors(30);
    assert(n30_after_remove.empty()); // Krawędź 30->10 usunięta

    std::list<int> n20_after_remove = g.neighbors(20);
    n20_after_remove.sort();
    assert(n20_after_remove.size() == 2); // Pozostały 20->30 i 20->5
    assert(n20_after_remove.front() == 5);
    assert(n20_after_remove.back() == 30);


    g.removeVertex(10); // Próba usunięcia nieistniejącego
    assert(g.size() == 3);

    // === Test save ===
    std::cout << "Test wywołania save()..." << std::endl;
    g.save("adtgraph_test_output");
    std::cout << "-> Plik 'adtgraph_test_output.txt' powinien zostać utworzony/nadpisany." << std::endl;

    std::cout << "Wszystkie testy ADTgraph zakończone pomyślnie!" << std::endl;

    return 0;
}