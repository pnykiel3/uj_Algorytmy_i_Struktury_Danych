#include <fstream>
#include <map>
#include <list>
#include <iostream>

class ADTgraph {

public:

// Klasa reprezentująca krawędź
    // Waga krawędzi oraz wierzchołek końcowy( -1, czyli krawedz nie prowadzi do niczego)
    struct Edge {
        int weight = 0;
        int end_node = -1;
    };

private:

    struct Node {
        std::string caption = "";
        int weight = 0;
        std::list<Edge> edges;
    };

    //indeks wierzcholka(ID) oraz Node zawierajacy informacje o nim
    // mapa robi to, ze wierzcholki sa posortowane po ID
    std::map<int, Node> graph;

public:

    // konstruktor pusty, bo mapa sama zajmie się inicjalizacją
    ADTgraph() {}

    
    void addVertex(int x, std::string caption = "") {
        // emplace nie wstawi elementu, jeśli klucz już istnieje
        // Drugi argument to konstruktor dla Node{} (pusty Node)
        graph.emplace(x, Node{caption});
    }

    void removeVertex(int x) {
        // Sprawdź, czy wierzchołek istnieje i usuń go
        auto it_x = graph.find(x);
        if (it_x == graph.end()) {
            return; // Wierzchołka nie ma
        }
        // usuwa wierzchołek z mapy wraz z krawędziami wychodzącymi z niego
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

    // Sprawdzanie, czy istnieje krawędź pomiędzy x oraz y
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

    // Zwraca sąsiadów wierzchołka x
    std::list<int> neighbors(int x) {
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

    void addUndirectedEdge(int x, int y) {
        addEdge(x, y);
        addEdge(y, x);
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

    void setVertexCaption(int x, std::string caption) {
        auto it_x = graph.find(x);
        if (it_x != graph.end()) {
            it_x->second.caption = caption;
        }
    }

    std::string getVertexCaption(int x) {
        auto it_x = graph.find(x);
        if (it_x != graph.end()) {
            return it_x->second.caption;
        }
        return "No"; // Dla nieistniejącego x
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

    // Zwraca listę wszystkich identyfikatorów wierzchołków w grafie
    std::list<int> getAllVertices() const {
        std::list<int> vertices_ids;
        for (const auto& pair : graph) {
            vertices_ids.push_back(pair.first);
        }
        return vertices_ids;
    }

    // Zapisuje graph do pliku
    void save(std::string filename, bool captions = false) {
        std::ofstream plik;
        plik.open(filename + ".txt");

        // Sprawdź, czy plik został poprawnie otwarty
        if (!plik.is_open()) {
            std::cerr << "Błąd: Nie można otworzyć pliku " << filename << ".txt" << std::endl;
            return;
        }

        plik << "digraph G {" << std::endl;
        if (captions) {
            for (const auto& para : graph) {
                for (const auto& edge : para.second.edges) {
                    plik << '\t' << "\"" << para.second.caption << "\"" << " -> " << "\"" << graph.at(edge.end_node).caption << "\"" << std::endl;
                }
                if (para.second.edges.empty()) {
                     plik << '\t' << para.first << ";" << std::endl;
                }
            }
        } else {
        // pętle po mapie i liście (klucz to ID wierzchołka, para.second to Node)
        for (const auto& para : graph) {
            for (const auto& edge : para.second.edges) {
                plik << '\t' << para.first << " -> " << edge.end_node << std::endl;
            }
            if (para.second.edges.empty()) {
                 plik << '\t' << para.second.caption << ";" << std::endl;
            }
        }
    }
        plik << "}";
        plik.close(); 
    }
};
