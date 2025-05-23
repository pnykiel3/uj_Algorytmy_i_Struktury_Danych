#include "../C/NEIGHBORgraph.h"

int main () {
	
	ADTgraph graf;
	graf.addVertex (1, "A-D"); // A-D
	graf.addVertex (2, "D-A"); // D-A
	graf.addVertex (3, "D-B"); // D-B
	graf.addVertex (4, "D-C"); // D-C
	graf.addVertex (5, "A-B"); // A-B
	graf.addVertex (6, "A-C"); // A-C
	graf.addVertex (7, "B-A"); // B-A
	graf.addVertex (8, "E-D"); // E-D
	graf.addVertex (9, "E-A"); // E-A
	graf.addVertex (10, "E-B"); // E-B
	graf.addVertex (11, "E-C"); // E-C
	graf.addVertex (12, "B-C"); // B-C
	graf.addVertex (13, "B-D"); // B-D
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
	
    std::string filename = "graf_D-2";
	graf.save (filename, 1);
    std::string cmd = "dot -Tpng " + filename + ".txt -o " + filename + ".jpg";
    system(cmd.c_str());
    return 0;
}