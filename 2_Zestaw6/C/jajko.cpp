#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>


#include "../../2_Zestaw5/C/NEIGHBORgraph.h"

void DFSrec(ADTgraph& graf, int v, std::map<int, bool>& odwiedzone, std::list<int>& stos) {
	
	odwiedzone[v] = true;
	
	// idziemy wgłąb grafu
	for (int i : graf.neighbors(v))
		if (odwiedzone[i] == false)
			DFSrec(graf, i, odwiedzone, stos);
	
	// dodajemy element na stos tylko wtedy gdy nie możemy już iść głębiej
	stos.push_front(v);
}

std::list<int> topologicalSort(ADTgraph& graf) {

	std::list<int> stos;
	
	// przypisujemy każdemy wierzchołkowi fałsz
	std::map<int, bool> odwiedzone;
	for (int i : graf.getAllVertices()) {
		odwiedzone[i] = false;
	}
	
	// dla każdego wierzchołka w grafie
	// idziemy wgłąb grafu aż trafimy na węzeł bez sąsiadów
	for (int i : graf.getAllVertices()) {
		if (odwiedzone [i] == false) {
			DFSrec(graf, i, odwiedzone, stos);
		}
	}
	
	return stos;
}

int main() {
	
	ADTgraph graf;
	
	// lista kroków
	graf.addVertex (1, "Weź 1 jajko");
	graf.addVertex (2, "Weź 1 łyżkę oleju");
	graf.addVertex (3, "Weź ¾ szklanki mleka");
	graf.addVertex (4, "Zmieszaj składniki");
	graf.addVertex (5, "Podgrzej syrop klonowy");
	graf.addVertex (6, "Zjedz rumiany naleśnik polany ciepłym syropem klonowym");
	graf.addVertex (7, "Nagrzej patelnię");
	graf.addVertex (8, "Wylej część ciasta naleśnikowego na patelnię");
	graf.addVertex (9, "Gdy naleśnik jest rumiany od spodu przewróć go i podpiecz z drugiej strony");
	// lista zależności pomiędzy krokami
	graf.addEdge(1, 4);
	graf.addEdge(2, 4);
	graf.addEdge(3, 4);
	graf.addEdge(4, 5);
	graf.addEdge(4, 8);
	graf.addEdge(7, 8);
	graf.addEdge(8, 9);
	graf.addEdge(9, 6);
	graf.addEdge(5, 6);
	
	std::cout << "Kolejność wykonywania kroków" << std::endl << std::endl;
	
	int i = 1;
	for (int node : topologicalSort(graf)) {
		std::cout << i << ". " << graf.getVertexCaption (node) << std::endl;
		i++;
	}
	
	return 0;
}