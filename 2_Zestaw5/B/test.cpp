#include <iostream>
#include "ADTgraph.h"

int main() {

    ADTgraph<20> graf;
	graf.addVertex (1);
	graf.addVertex (2);
	graf.addVertex (3);
	graf.addVertex (4);
	graf.addVertex (5);
	graf.addVertex (6);
	graf.addVertex (7);
	graf.addVertex (8);
	graf.addVertex (9);
	graf.addVertex (10);
	graf.addVertex (11);
	graf.addVertex (12);
	graf.addVertex (13);
	graf.addEdge (1, 10);
	graf.addEdge (1, 6);
	graf.addEdge (1, 5);
	graf.addEdge (1, 7);
	graf.addEdge (1, 11);
	graf.addEdge (1, 8);
	graf.addEdge (2, 10);
	graf.addEdge (2, 6);
	graf.addEdge (2, 5);
	graf.addEdge (2, 11);
	graf.addEdge (2, 12);
	graf.addEdge (2, 7);
	graf.addEdge (2, 8);
	graf.addEdge (2, 9);
	graf.addEdge (3, 10);
	graf.addEdge (3, 11);
	graf.addEdge (3, 12);
	graf.addEdge (3, 13);
	graf.addEdge (3, 6);
	graf.addEdge (4, 7);
	graf.addEdge (4, 10);
	graf.addEdge (5, 1);
	graf.addEdge (5, 11);
	graf.addEdge (5, 7);
	graf.addEdge (5, 8);
	graf.addEdge (5, 9);
	graf.addEdge (5, 2);
	graf.addEdge (5, 12);
	graf.addEdge (6, 7);
	graf.addEdge (6, 1);
	graf.addEdge (6, 2);
	graf.addEdge (6, 3);
	graf.addEdge (6, 11);
	graf.addEdge (6, 12);
	graf.addEdge (6, 13);
	graf.addEdge (7, 12);
	graf.addEdge (7, 11);
	graf.addEdge (7, 2);
	graf.addEdge (7, 2);
	graf.addEdge (7, 5);
	graf.addEdge (7, 6);
	graf.addEdge (7, 4);
	graf.addEdge (7, 10);
	graf.addEdge (8, 2);
	graf.addEdge (8, 1);
	graf.addEdge (8, 5);
	graf.addEdge (8, 12);
	graf.addEdge (8, 11);
	graf.addEdge (9, 2);
	graf.addEdge (9, 12);
	graf.addEdge (9, 5);
	graf.addEdge (10, 1);
	graf.addEdge (10, 2);
	graf.addEdge (10, 3);
	graf.addEdge (10, 7);
	graf.addEdge (10, 4);
	graf.addEdge (11, 3);
	graf.addEdge (11, 2);
	graf.addEdge (11, 1);
	graf.addEdge (11, 7);
	graf.addEdge (11, 8);
	graf.addEdge (11, 5);
	graf.addEdge (11, 6);
	graf.addEdge (12, 3);
	graf.addEdge (12, 2);
	graf.addEdge (12, 6);
	graf.addEdge (12, 5);
	graf.addEdge (12, 7);
	graf.addEdge (12, 8);
	graf.addEdge (12, 9);
	graf.addEdge (13, 3);
	graf.addEdge (13, 6);
	
    // Testuj funkcję print
    graf.print("testGraphB");

    std::cout << "Plik testGraph.txt został wygenerowany.\n";
    return 0;
}