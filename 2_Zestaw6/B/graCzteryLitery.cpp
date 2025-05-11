// PROGRAM NIE OBSLUGUJE POLSKICH ZNAKOW
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <deque>
#include <chrono>
#include <ctime>
#include <cstdlib>

using Buckets = std::map<std::string, std::vector<std::string>>;
using Graph = std::map<std::string, std::set<std::string>>;

std::vector<std::string> fileToVector(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "[E] Nie mozna otworzyc pliku " << filename << std::endl;
        return words;
    }
    std::string word;
    while (std::getline(file, word)) {
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    file.close();
    return words;
}

Graph buildGraph(std::vector<std::string>& words) {
    Graph graph;
    Buckets buckets;

    // podzial slow do bucketow
    for (const std::string& word : words) {
        for (size_t i = 0; i < word.size(); ++i) {
            std::string prefix = word.substr(0, i);
            std::string suffix = word.substr(i + 1);
            std::string bucket_key = prefix + "_" + suffix;
            buckets[bucket_key].push_back(word);
        }
    }

    // dodawanie wierzcholkow i krawedzi dla slow w tym samym bucket
    for (const auto& pair : buckets) {

        const std::vector<std::string>& mutal_neighbors = pair.second;
       for (const std::string& word1 : mutal_neighbors) {
            for (const std::string& word2 : mutal_neighbors) {
                if (word1 != word2) {
                    graph[word1].insert(word2);
                    graph[word2].insert(word1); // bo graf jest nieskierowany
                }
            }
        }
    }
    return graph;
}

std::vector<std::string> traverse(const Graph& graph, const std::string& startVertex, std::string& targetVertex) {
    std::set<std::string> visited;
    std::deque<std::vector<std::string>> queue;
    queue.push_back({startVertex});

    while (!queue.empty()) {
        std::vector<std::string> path = queue.front();
        queue.pop_front();
        std::string vertex = path.back();
        if (vertex == targetVertex) {
            return path;
        }
        auto it = graph.find(vertex);
        if (it != graph.end()) {
            const std::set<std::string>& neighbors = it->second; // Pobieramy zbiór sąsiadów
            for (const std::string& neighbor : neighbors) {
                // Jeśli sąsiad nie był jeszcze odwiedzony
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor); // Oznaczamy sąsiada jako odwiedzonego
                    std::vector<std::string> new_path = path; // Kopiujemy bieżącą ścieżkę
                    new_path.push_back(neighbor); // Dodajemy sąsiada do nowej ścieżki
                    queue.push_back(new_path); // Dodajemy nową ścieżkę do kolejki
                }
            }
        }
    }        
    // Jeśli pętla zakończyła się, a wierzchołek docelowy nie został znaleziony
    return {}; // Zwraca pusty wektor
}

void wypiszWektor(const std::vector<std::string>& v) {
    for (const auto& element : v) {
        if (element != v.back()) {
            std::cout << element << "  ->  ";
        } else {
            std::cout << element;
        }
    }
    std::cout << std::endl;
}

int main() {
    std::string filename = "cztery_litery.txt";
    std::vector<std::string> slowka = fileToVector(filename);
    Graph g = buildGraph(slowka);
    std::string start;
    std::string target;
    std::cout << "[UWAGA] Program nie obsluguje polskich znakow!" << std::endl;
    std::cout << "Wprowadz czteroliterowe slowo startowe: ";
    std::cin >> start;
    std::cout << "Wprowadz czteroliterowe slowo docelowe: ";
    std::cin >> target;
    auto startTime = std::chrono::high_resolution_clock::now();
    std::vector<std::string> path = traverse(g, start, target);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    auto durationInSeconds = static_cast<double>(duration) / 1'000'000'000.0;
    std::cout << "Czas wykonania: " << duration << " ns," << " czyli " << durationInSeconds << " s" << std::endl;
    std::cout << "Wielkosc grafu: " << g.size() << std::endl;
    std::cout << "Liczba krawedzi: ";
    int edgeCount = 0;
    for (const auto& pair : g) {
        edgeCount += pair.second.size();
    }
    std::cout << edgeCount / 2 << std::endl; // Dzielimy przez 2, bo graf jest nieskierowany

    if (path.empty()) {
        std::cout << "Nie znaleziono sciezki z " << start << " do " << target << std::endl;
    } else {
        std::cout << "Znaleziono sciezke z " << start << " do " << target << ": ";
        wypiszWektor(path);
    }
}
