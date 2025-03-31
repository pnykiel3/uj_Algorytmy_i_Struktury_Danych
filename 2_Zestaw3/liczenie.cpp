#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <fstream>
#include "priorityQueueBinary.h"
#include "priorityQueue.h"

// Konfiguracja pomiarów
const int NUM_INITIAL_ELEMENTS = 1000; // elementy wstawiane na poczatek kopca
const int MAX_VALUE = 1000000;
const int MAX_HEAP_SIZE = 100000;
const int MEASUREMENTS_PER_POINT = 100;
const int MEASUREMENT_INTERVAL = 150;
const int FINAL_SIZE = 1000000;

// Funkcja generująca wektor losowych liczb całkowitych
std::vector<int> generate_random_data(int count) {
    std::vector<int> data;
    data.reserve(count);
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dis(0, MAX_VALUE);
    for (int i = 0; i < count; i++) {
        data.push_back(dis(gen));
    }
    return data;
}



// Szablon do pomiaru czasu wykonania operacji (w nanosekundach)
template<typename Func>
long long measure_time(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}


void measure_function(std::ofstream& filename, std::function<void(BinaryHeap&)> func) {
    long long mtotalDuration = 0;
    int measurementsTaken = 0;

    std::vector<int> elements = generate_random_data(FINAL_SIZE);
    BinaryHeap myheap;

    // Inicjalizacja początkowymi elementami
    for (int i = 0; i < NUM_INITIAL_ELEMENTS; ++i) {
        myheap.insert(elements[i]);
    }
    for (int currentSize = NUM_INITIAL_ELEMENTS; currentSize < FINAL_SIZE; currentSize+=MEASUREMENT_INTERVAL) {

        // Stwórz nowy wektor zawierający elementy do dodania i je dodaj
        std::vector<int> sub_elements(elements.begin() + currentSize, elements.begin() + currentSize + MEASUREMENT_INTERVAL);
        for (int val : sub_elements) {
            myheap.insert(val);
        }

        for (int i = 0; i < MEASUREMENTS_PER_POINT; i++) {
            mtotalDuration += measure_time([&]() { func(myheap); });
            measurementsTaken++;
        }
        double averageTime = static_cast<double>(mtotalDuration) / measurementsTaken;
        filename << currentSize << " " << averageTime << "\n";

    }
}



// Pomiar złożoności wstawiania (insert)
void measureInsert(std::ofstream& outFile) {
    std::vector<int> elements = generate_random_data(FINAL_SIZE);
    BinaryHeap heap;

    // Inicjalizacja początkowymi elementami
    for (int i = 0; i < NUM_INITIAL_ELEMENTS; ++i) {
        heap.insert(elements[i]);
    }

    int elemIndex = NUM_INITIAL_ELEMENTS;
    for (int currentSize = NUM_INITIAL_ELEMENTS; currentSize < FINAL_SIZE && elemIndex < elements.size(); currentSize += MEASUREMENT_INTERVAL) {
        long long totalDuration = 0;
        int measurementsTaken = 0;
        for (int m = 0; m < MEASUREMENTS_PER_POINT && elemIndex < elements.size(); ++m) {
            totalDuration += measure_time([&]() { heap.insert(elements[elemIndex++]); });
            measurementsTaken++;
        }
        if (measurementsTaken == 0) break;
        double averageTime = static_cast<double>(totalDuration) / measurementsTaken;
        outFile << currentSize << " " << averageTime << "\n";
        std::cout << "[insert] Size: " << currentSize << " | Avg time: " << averageTime << " ns" << std::endl;
    }
}


void measureAinsert(std::ofstream& filename) {
    std::vector<int> elementsV = generate_random_data(FINAL_SIZE);
    std::vector<int> elementsP = generate_random_data(FINAL_SIZE);
    priorityQueue<int> myheap;
    // Inicjalizacja początkowymi elementami
    for (int i = 0; i < NUM_INITIAL_ELEMENTS; ++i) {
        myheap.push(elementsV[i], elementsP[i]);
    }
    int elemIndex = NUM_INITIAL_ELEMENTS;

    for (int currentSize = NUM_INITIAL_ELEMENTS; currentSize < FINAL_SIZE; currentSize+=MEASUREMENT_INTERVAL) {
        long long totalDuration = 0;
        int measurementsTaken = 0;
        for (int m = 0; m < MEASUREMENTS_PER_POINT && elemIndex < elementsV.size(); ++m) {
            totalDuration += measure_time([&]() { myheap.push(elementsV[elemIndex], elementsP[elemIndex++]); });
            measurementsTaken++;
        }
        if (measurementsTaken == 0) break;
        double averageTime = static_cast<double>(totalDuration) / measurementsTaken;
        filename << currentSize << " " << averageTime << "\n";
        std::cout << "[A_insert] Size: " << currentSize << " | Avg time: " << averageTime << " ns" << std::endl;
    }
}


// Pomiar budowania kopca (build_heap)
void measureBuildHeap(std::ofstream& outFile) {
    std::vector<int> elements = generate_random_data(FINAL_SIZE);
    // W miarę zwiększania rozmiaru tablicy do zbudowania kopca
    for (int currentSize = NUM_INITIAL_ELEMENTS; currentSize <= FINAL_SIZE; currentSize += MEASUREMENT_INTERVAL) {
        long long duration = measure_time([&]() {
            BinaryHeap heap;
            heap.build_heap(elements.data(), currentSize);
        });
        outFile << currentSize << " " << duration << "\n";
        std::cout << "[build_heap] Size: " << currentSize << " | Time: " << duration << " ns" << std::endl;
    }
}

int main() {

    std::ofstream outFileInsert("data/time_insert.dat");
    std::ofstream outFileBuild("data/time_build_heap.dat");
    std::ofstream outFileFindMin("data/time_find_min.dat");
    std::ofstream outFileIsEmpty("data/time_is_empty.dat");
    std::ofstream outFileSize("data/time_size.dat");
    std::ofstream outFileDelMin("data/time_del_min.dat");
    std::ofstream outA("data/a_insert.dat");

    if (!outFileInsert || !outFileBuild || !outFileFindMin ||
        !outFileIsEmpty || !outFileSize || !outFileDelMin || !outA) {
        std::cerr << "Błąd otwarcia pliku do zapisu." << std::endl;
        return 1;
    }

    std::cout << "Pomiar czasu operacji: " << std::endl;
    measureInsert(outFileInsert);
    measureBuildHeap(outFileBuild);
    measure_function(outFileDelMin, [](BinaryHeap& h) { h.del_min(); });
    measure_function(outFileFindMin, [](BinaryHeap& h) { h.find_min(); });
    measure_function(outFileIsEmpty, [](BinaryHeap& h) { h.is_empty(); });
    measure_function(outFileSize, [](BinaryHeap& h) { h.size(); });
    measureAinsert(outA);

    outFileInsert.close();
    outFileBuild.close();
    outFileDelMin.close();
    outFileFindMin.close();
    outFileIsEmpty.close();
    outFileSize.close();
    outA.close();
    std::cout << "Pomiary zakończone." << std::endl;
    return 0;
}