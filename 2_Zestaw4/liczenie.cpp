#include <iostream>
#include <fstream>
#include <chrono>
#include "ADTgraph.h"

const int MAX_GRAPH_SIZE = 1000;      // maksymalny rozmiar grafu
const int MEASUREMENTS_PER_POINT = 100; // liczba powtórzeń dla każdego rozmiaru

// Pomiar czasu dodawania wierzchołka
void measureAddVertex(std::ofstream& out) {
    for (int size = 10; size <= MAX_GRAPH_SIZE; size += 10) {
        long long totalTime = 0;
        for (int rep = 0; rep < MEASUREMENTS_PER_POINT; ++rep) {
            ADTgraph<MAX_GRAPH_SIZE + 10> g;
            // Dodaj size-1 wierzchołków
            for (int i = 0; i < size - 1; ++i) g.addVertex(i);
            int v = size - 1;
            auto start = std::chrono::high_resolution_clock::now();
            g.addVertex(v);
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        double avgTime = static_cast<double>(totalTime) / MEASUREMENTS_PER_POINT;
        out << size << " " << avgTime << "\n";
        std::cout << "[addVertex] Rozmiar: " << size << " | Średni czas: " << avgTime << " ns\n";
    }
}

// Pomiar czasu usuwania wierzchołka
void measureRemoveVertex(std::ofstream& out) {
    for (int size = 10; size <= MAX_GRAPH_SIZE; size += 10) {
        long long totalTime = 0;
        for (int rep = 0; rep < MEASUREMENTS_PER_POINT; ++rep) {
            ADTgraph<MAX_GRAPH_SIZE + 10> g;
            // Dodaj size wierzchołków
            for (int i = 0; i < size; ++i) g.addVertex(i);
            int v = size - 1;
            auto start = std::chrono::high_resolution_clock::now();
            g.removeVertex(v);
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        double avgTime = static_cast<double>(totalTime) / MEASUREMENTS_PER_POINT;
        out << size << " " << avgTime << "\n";
        std::cout << "[removeVertex] Rozmiar: " << size << " | Średni czas: " << avgTime << " ns\n";
    }
}

int main() {
    std::ofstream outAdd("data/time_addVertex50.dat");
    std::ofstream outRem("data/time_removeVertex50.dat");
    if (!outAdd || !outRem) {
        std::cerr << "Błąd otwarcia pliku do zapisu.\n";
        return 1;
    }

    measureAddVertex(outAdd);
    measureRemoveVertex(outRem);

    outAdd.close();
    outRem.close();
    std::cout << "Pomiary zakończone.\n";
    return 0;
}