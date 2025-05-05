#include <fstream>
#include <map>
#include <list>
#include <iostream>

class ADTgraph {

public:

    struct Edge {
        int weight = 0;
        int end_node = -1;
    };

private:

    struct Node {
        int weight = 0;
        std::list<Edge> edges;
    };

    
    std::map<int, Node> graph;

public:

    ADTgraph() {}

    
    void addVertex(int x) {
        // emplace nie wstawi elementu, jeśli klucz już istnieje
        // Drugi argument to konstruktor dla Node{} (pusty Node)
        graph.emplace(x, Node{});
    }

    void removeVertex(int x) {
        // Sprawdź, czy wierzchołek istnieje i usuń go
        auto it_x = graph.find(x);
        if (it_x == graph.end()) {
            return; // Wierzchołka nie ma
        }
        graph.erase(it_x);

        // Usuń krawędzie wchodzące do x z innych wierzchołków
        for (auto& para : graph) { // Iteruj przez referencje, by modyfikować listy
            Node& node = para.second;
            // Użyj remove_if z lambdą do usunięcia krawędzi wskazujących na x
            node.edges.remove_if([x](const Edge& edge) {
                return edge.end_node == x;
            });
        }
    }

    // Sprawdzanie, czy istnieje krawędź pomiędzy x oraz y (użycie find i pętli const auto&)
    bool adjacent(int x, int y) {
        auto it_x = graph.find(x);
        if (it_x == graph.end()) {
            return false; // Wierzchołek x nie istnieje
        }

        //Pętla po liście krawędzi
        for (const auto& edge : it_x->second.edges) {
            if (edge.end_node == y) {
                return true;
            }
        }
        return false;
    }

    // Zwraca sąsiadów x (użycie find i pętli const auto&)
    std::list<int> neighbours(int x) {
        std::list<int> nodes;
        auto it_x = graph.find(x);
        if (it_x != graph.end()) { // Sprawdź, czy wierzchołek x istnieje
            for (const auto& edge : it_x->second.edges) {
                nodes.push_back(edge.end_node);
            }
        }
        return nodes;
    }

    // Dodaje krawędź pomiędzy x i y
    void addEdge(int x, int y) {
        auto it_x = graph.find(x);
        auto it_y = graph.find(y); // Czy istnienie x, y

        if (it_x != graph.end() && it_y != graph.end()) {
            // emplace_back do skonstruowania Edge bezpośrednio na liście
             it_x->second.edges.emplace_back(Edge{0, y}); // Edge
        }
    }

    // Usuwa krawędź pomiędzy x i y
    void removeEdge(int x, int y) {
        auto it_x = graph.find(x);
        if (it_x != graph.end()) {
            // Usuń pierwszą napotkaną krawędź z x do y
            auto& edges_list = it_x->second.edges;
            for (auto it_edge = edges_list.begin(); it_edge != edges_list.end(); ++it_edge) {
                if (it_edge->end_node == y) {
                    edges_list.erase(it_edge);
                    return; // Usuń tylko pierwszą znalezioną i zakończ
                }
            }
        }
    }

    // Kojarzy wartość v z wierzchołkiem x 
    void setVertexValue(int x, int v) {
        auto it_x = graph.find(x);
        if (it_x != graph.end()) {
            it_x->second.weight = v;
        }
    }

    // Zwraca wartość skojarzoną z x
    int getVertexValue(int x) {
        auto it_x = graph.find(x);
        if (it_x != graph.end()) {
            return it_x->second.weight;
        }
        return -1; // Dla nieistniejącego x
    }

    // Kojarzy wartość v z krawędzią pomiędzy x oraz y
    void setEdgeValue(int x, int y, int v) {
        auto it_x = graph.find(x);
        if (it_x != graph.end()) {
            for (Edge& edge : it_x->second.edges) {
                if (edge.end_node == y) {
                    edge.weight = v;
                    // Jeśli chcemy ustawić tylko dla pierwszej napotkanej krawędzi x->y:
                    return; // Zakończ po znalezieniu i ustawieniu pierwszej
                }
            }
        }
    }

    // Zwraca wartość skojarzoną z krawędzią pomiędzy x oraz y
    int getEdgeValue(int x, int y) {
        auto it_x = graph.find(x);
        if (it_x != graph.end()) {
            for (const auto& edge : it_x->second.edges) {
                if (edge.end_node == y) {
                    return edge.weight; // Zwróć wagę pierwszej napotkanej
                }
            }
        }
        return -1; // Dla nieistniejącej krawędzi
    }

    // Zwraca rozmiar grafu
    int size() {
        return graph.size();
    }

    // Zapisuje graph do pliku
    void save(std::string filename) {
        std::ofstream plik;
        plik.open(filename + ".txt");

        // Sprawdź, czy plik został poprawnie otwarty
        if (!plik.is_open()) {
            std::cerr << "Błąd: Nie można otworzyć pliku " << filename << ".txt" << std::endl;
            return;
        }

        plik << "digraph G {" << std::endl;
        // pętle po mapie i liście (klucz to ID wierzchołka, para.second to Node)
        for (const auto& para : graph) {
            for (const auto& edge : para.second.edges) {
                plik << '\t' << para.first << " -> " << edge.end_node << std::endl;
            }
            if (para.second.edges.empty()) {
                 plik << '\t' << para.first << ";" << std::endl;
            }
        }
        plik << "}";
        plik.close(); 
    }
};
