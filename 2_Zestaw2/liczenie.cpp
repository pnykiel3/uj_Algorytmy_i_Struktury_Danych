#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "setHashed.h"

using namespace std;
using namespace std::chrono;

// Wspólne parametry konfiguracyjne
const int NUM_INITIAL_ELEMENTS = 100;
const int FINAL_SIZE = 500000;
const int MEASUREMENT_INTERVAL = 20;
const int MEASUREMENTS_PER_POINT = 1000;
const int MAX_VALUE = 2000000000;

template<typename Func>
long long measure_time(Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto stop = high_resolution_clock::now();
    return duration_cast<nanoseconds>(stop - start).count();
}

vector<int> generate_unique_elements(int count) {
    unordered_set<int> uniqueSet;
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dis(0, MAX_VALUE);

    while(uniqueSet.size() < count) {
        uniqueSet.insert(dis(gen));
    }

    vector<int> elements(uniqueSet.begin(), uniqueSet.end());
    std::shuffle(elements.begin(), elements.end(), gen);
    return elements;
}

// 1. Pomiar wstawiania
template<typename SetType>
void insertComplexity(ofstream& outFile) {
    SetType mySet;
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dis(0, MAX_VALUE);

    // Generowanie unikalnych wartości
    cout << "Generating test data... ";
    unordered_set<int> uniqueElements;
    while (uniqueElements.size() < FINAL_SIZE) {
        uniqueElements.insert(dis(gen));
    }
    vector<int> elements(uniqueElements.begin(), uniqueElements.end());
    std::shuffle(elements.begin(), elements.end(), gen);
    cout << "Done (" << elements.size() << " unique elements generated)" << endl;

    // Inicjalizacja początkowymi elementami
    cout << "Initializing set... ";
    for (int i = 0; i < min(NUM_INITIAL_ELEMENTS, (int)elements.size()); ++i) {
        mySet.insert(elements[i]);
    }
    cout << "Done (" << mySet.getSize() << " initial elements)" << endl;

    // Główna pętla pomiarowa
    cout << "Starting measurements..." << endl;
    int elemIndex = NUM_INITIAL_ELEMENTS;

    for (int currentSize = NUM_INITIAL_ELEMENTS;
         currentSize < FINAL_SIZE && elemIndex < elements.size();
         currentSize += MEASUREMENT_INTERVAL) {

        long long totalDuration = 0;
        int measurementsTaken = 0;

        // Wykonaj pomiary dla aktualnego rozmiaru
        for (int m = 0; m < MEASUREMENTS_PER_POINT && elemIndex < elements.size(); ++m) {
            totalDuration += measure_time([&]() { mySet.insert(elements[elemIndex++]); });
            measurementsTaken++;
        }

        if (measurementsTaken == 0) break; // Zabezpieczenie przed dzieleniem przez zero

        double averageTime = static_cast<double>(totalDuration) / measurementsTaken;
        outFile << currentSize << " " << averageTime << endl;

        // Dodaj elementy pomiędzy punktami pomiarowymi (bez mierzenia)
        for (int i = 0; i < MEASUREMENT_INTERVAL - MEASUREMENTS_PER_POINT && elemIndex < elements.size(); ++i) {
            mySet.insert(elements[elemIndex++]);
        }

        cout << "[insert] Size: " << currentSize
             << " | Avg time: " << averageTime << " ns"
             << " | Elements inserted: " << elemIndex << "/" << FINAL_SIZE << endl;
        if (averageTime > 2000000) {
            cout << "Time is too long" << endl;
            return;
        }
    }
}

// 2. Pomiar usuwania
template<typename SetType>
void removeComplexity(ofstream& outFile) {
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dis(0, MAX_VALUE);

    // Generowanie unikalnych wartości
    cout << "Generating test data... ";
    unordered_set<int> uniqueElements;
    while (uniqueElements.size() < FINAL_SIZE) {
        uniqueElements.insert(dis(gen));
    }
    vector<int> elements(uniqueElements.begin(), uniqueElements.end());
    std::shuffle(elements.begin(), elements.end(), gen);
    cout << "Done (" << elements.size() << " unique elements generated)" << endl;

    // Główna pętla pomiarowa
    cout << "Starting measurements..." << endl;

    for (int currentSize = NUM_INITIAL_ELEMENTS;
         currentSize < FINAL_SIZE;
         currentSize += MEASUREMENT_INTERVAL) {

        SetType mySet;
        vector<int> currentElements(elements.begin(), elements.begin() + currentSize);
        std::shuffle(currentElements.begin(), currentElements.end(), gen);

        // Inicjalizacja zbioru
        for (int val : currentElements) {
            mySet.insert(val);
        }

        long long totalDuration = 0;
        uniform_int_distribution<> indexDis(0, currentSize - 1);

        // Wykonaj pomiary
        for (int m = 0; m < MEASUREMENTS_PER_POINT; ++m) {
            int idx = indexDis(gen);
            int target = currentElements[idx];

            totalDuration += measure_time([&]() {
                mySet.remove(target);
            });

            mySet.insert(target); // Przywróć element
        }

        double averageTime = static_cast<double>(totalDuration) / MEASUREMENTS_PER_POINT;
        outFile << currentSize << " " << averageTime << endl;

        cout << "[remove] Size: " << currentSize
             << " | Avg remove time: " << averageTime << " ns"
             << " | Elements tested: " << currentSize << endl;

        if (averageTime > 10000) {
            cout << "Time is too long" << endl;
            return;
        }
         }

}

// 3. Pomiar sumy
template<typename SetType>
void sumComplexity(ofstream& outFile) {
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dis(0, MAX_VALUE);

    // Generowanie unikalnych wartości (2x FINAL_SIZE)
    cout << "Generating test data... ";
    unordered_set<int> uniqueElements;
    while (uniqueElements.size() < 2 * FINAL_SIZE) {
        uniqueElements.insert(dis(gen));
    }
    vector<int> elements(uniqueElements.begin(), uniqueElements.end());
    std::shuffle(elements.begin(), elements.end(), gen);
    cout << "Done (" << elements.size() << " unique elements generated)" << endl;

    // Główna pętla pomiarowa
    cout << "Starting measurements..." << endl;

    for (int currentSize = NUM_INITIAL_ELEMENTS;
         currentSize < FINAL_SIZE;
         currentSize += MEASUREMENT_INTERVAL) {

        // Przygotowanie zbiorów A i B z 50% pokryciem
        SetType setA, setB;
        const int overlapStart = currentSize / 2;

        // Wypełnianie zbioru A
        for(int i = 0; i < currentSize; ++i) {
            setA.insert(elements[i]);
        }

        // Wypełnianie zbioru B (50% wspólne + 50% unikalne)
        for(int i = overlapStart; i < overlapStart + currentSize; ++i) {
            setB.insert(elements[i]);
        }

        long long totalDuration = 0;

        // Wykonaj pomiary
        for(int m = 0; m < MEASUREMENTS_PER_POINT; ++m) {
            totalDuration += measure_time([&](){
                setA.sum(setB);
            });
        }

        double averageTime = static_cast<double>(totalDuration) / MEASUREMENTS_PER_POINT;
        outFile << currentSize << " " << averageTime << endl;

        cout << "[sum] Size: " << currentSize
             << " | Avg sum time: " << averageTime << " ns"
             << " | Overlap: " << (currentSize - overlapStart) << "/" << currentSize << endl;
        if (averageTime > 2000000) {
            cout << "Time is too long" << endl;
            return;
        }
         }

}

// 4. Pomiar części wspólnej
template<typename SetType>
void intersectionComplexity(ofstream& outFile) {
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dis(0, MAX_VALUE);

    // Generowanie unikalnych wartości (2x FINAL_SIZE)
    cout << "Generating test data... ";
    unordered_set<int> uniqueElements;
    while (uniqueElements.size() < 2 * FINAL_SIZE) {
        uniqueElements.insert(dis(gen));
    }
    vector<int> elements(uniqueElements.begin(), uniqueElements.end());
    std::shuffle(elements.begin(), elements.end(), gen);
    cout << "Done (" << elements.size() << " unique elements generated)" << endl;

    // Główna pętla pomiarowa
    cout << "Starting measurements..." << endl;

    for (int currentSize = NUM_INITIAL_ELEMENTS;
         currentSize < FINAL_SIZE;
         currentSize += MEASUREMENT_INTERVAL) {

        // Przygotowanie zbiorów A i B z 50% pokryciem
        SetType setA, setB;
        const int overlapSize = currentSize / 2;

        // Wypełnianie zbioru A
        for(int i = 0; i < currentSize; ++i) {
            setA.insert(elements[i]);
        }

        // Wypełnianie zbioru B (50% wspólne + 50% unikalne)
        for(int i = 0; i < overlapSize; ++i) {
            setB.insert(elements[i]); // Część wspólna
        }
        for(int i = FINAL_SIZE; i < FINAL_SIZE + currentSize - overlapSize; ++i) {
            setB.insert(elements[i]); // Część unikalna
        }

        long long totalDuration = 0;

        // Wykonaj pomiary
        for(int m = 0; m < MEASUREMENTS_PER_POINT; ++m) {
            totalDuration += measure_time([&](){
                setA.intersection(setB);
            });
        }

        double averageTime = static_cast<double>(totalDuration) / MEASUREMENTS_PER_POINT;
        outFile << currentSize << " " << averageTime << endl;

        cout << "[intersection] Size: " << currentSize
             << " | Avg intersection time: " << averageTime << " ns"
             << " | Overlap: " << overlapSize << "/" << currentSize << endl;
        if (averageTime > 2000000) {
            cout << "Time is too long" << endl;
            return;
        }
    }
}

// 5. Pomiar zawartości
template<typename SetType>
void containsComplexity(ofstream& outFile) {
    SetType mySet;
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dis(0, MAX_VALUE);

    // Generowanie unikalnych wartości
    cout << "Generating test data... ";
    unordered_set<int> uniqueElements;
    while (uniqueElements.size() < FINAL_SIZE) {
        uniqueElements.insert(dis(gen));
    }
    vector<int> elements(uniqueElements.begin(), uniqueElements.end());
    std::shuffle(elements.begin(), elements.end(), gen);
    cout << "Done (" << elements.size() << " unique elements generated)" << endl;

    // Inicjalizacja początkowymi elementami
    cout << "Initializing set... ";
    for (int i = 0; i < min(NUM_INITIAL_ELEMENTS, (int)elements.size()); ++i) {
        mySet.insert(elements[i]);
    }
    cout << "Done (" << mySet.getSize() << " initial elements)" << endl;

    // Główna pętla pomiarowa
    cout << "Starting measurements..." << endl;
    int elemIndex = NUM_INITIAL_ELEMENTS;

    for (int currentSize = NUM_INITIAL_ELEMENTS;
         currentSize < FINAL_SIZE && elemIndex < elements.size();
         currentSize += MEASUREMENT_INTERVAL) {

        long long totalDuration = 0;
        int measurementsTaken = 0;

        // Wykonaj pomiary dla aktualnego rozmiaru
        for (int m = 0; m < MEASUREMENTS_PER_POINT && elemIndex < elements.size(); ++m) {
            totalDuration += measure_time([&]() { mySet.contains(elements[elemIndex++]); });
            measurementsTaken++;
        }

        if (measurementsTaken == 0) break; // Zabezpieczenie przed dzieleniem przez zero

        double averageTime = static_cast<double>(totalDuration) / measurementsTaken;
        outFile << currentSize << " " << averageTime << endl;

        // Dodaj elementy pomiędzy punktami pomiarowymi (bez mierzenia)
        for (int i = 0; i < MEASUREMENT_INTERVAL - MEASUREMENTS_PER_POINT && elemIndex < elements.size(); ++i) {
            mySet.insert(elements[elemIndex++]);
        }

        cout << "[contains] Size: " << currentSize
             << " | Avg time: " << averageTime << " ns"
             << " | Elements checked: " << elemIndex << "/" << FINAL_SIZE << endl;
        if (averageTime > 2000000) {
            cout << "Time is too long" << endl;
            return;
        }
    }
}

// 6. Pomiar równości
template<typename SetType>
void equalityComplexity(ofstream& outFile) {
    try {
        // 1. Inicjalizacja generatora liczb losowych
        random_device rd;
        if (rd.entropy() == 0) {
            throw runtime_error("Generator liczb losowych nie działa prawidłowo");
        }
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, MAX_VALUE);

        // 2. Generowanie danych z kontrolą pamięci
        cout << "Generating test data... ";
        vector<int> elements;
        {
            unordered_set<int> uniqueElements;
            while (uniqueElements.size() < static_cast<size_t>(FINAL_SIZE)) {
                uniqueElements.insert(dis(gen));
            }
            elements.reserve(uniqueElements.size());
            elements.assign(uniqueElements.begin(), uniqueElements.end());
        }
        shuffle(elements.begin(), elements.end(), gen);
        cout << "Done (" << elements.size() << " elements)" << endl;

        // 3. Główna pętla pomiarowa
        cout << "Starting measurements..." << endl;
        for (int currentSize = NUM_INITIAL_ELEMENTS;
             currentSize <= FINAL_SIZE && currentSize <= elements.size();
             currentSize += MEASUREMENT_INTERVAL) {

            // 4. Przygotowanie zbiorów z walidacją
            SetType setA, setB;
            for (int i = 0; i < currentSize; ++i) {
                if (i >= elements.size()) {
                    throw out_of_range("elements[] out of bounds at i=" + to_string(i));
                }
                setA.insert(elements[i]);
                setB.insert(elements[i]);
            }

            // 5. Pomiar czasu z dodatkowymi zabezpieczeniami
            long long totalDuration = 0;
            for (int m = 0; m < MEASUREMENTS_PER_POINT; ++m) {
                totalDuration += measure_time([&]() {
                    if (!setA.equals(setB)) { // <-- Podejrzany punkt!
                        throw logic_error("Zbiory powinny być identyczne");
                    }
                });
            }

            double avgTime = static_cast<double>(totalDuration) / MEASUREMENTS_PER_POINT;
            outFile << currentSize << " " << avgTime << endl;

            cout << "[equals] Size: " << currentSize
                 << " | Avg time: " << avgTime << " ns" << endl;

            if (avgTime > 2'000'000) {
                cout << "Przekroczono limit czasu" << endl;
                break;
            }
        }
    } catch (const exception& e) {
        cerr << "BŁĄD: " << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

// 7. Pomiar różnicy
template<typename SetType>
void differenceComplexity(ofstream& outFile) {
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dis(0, MAX_VALUE);

    // Generowanie unikalnych wartości
    cout << "Generating test data... ";
    unordered_set<int> uniqueElements;
    while (uniqueElements.size() < 2 * FINAL_SIZE) {
        uniqueElements.insert(dis(gen));
    }
    vector<int> elements(uniqueElements.begin(), uniqueElements.end());
    std::shuffle(elements.begin(), elements.end(), gen);
    cout << "Done (" << elements.size() << " unique elements generated)" << endl;

    // Główna pętla pomiarowa
    cout << "Starting measurements..." << endl;

    for (int currentSize = NUM_INITIAL_ELEMENTS;
         currentSize < FINAL_SIZE;
         currentSize += MEASUREMENT_INTERVAL) {

        // Przygotowanie zbiorów A i B
        SetType setA, setB;
        const int overlapCount = currentSize / 3; // 33% pokrycia

        // Wypełnianie zbioru A
        for(int i = 0; i < currentSize; ++i) {
            setA.insert(elements[i]);
        }

        // Wypełnianie zbioru B (część wspólna + unikalne)
        for(int i = 0; i < overlapCount; ++i) {
            setB.insert(elements[i]); // Elementy wspólne
        }
        for(int i = FINAL_SIZE; i < FINAL_SIZE + currentSize - overlapCount; ++i) {
            setB.insert(elements[i]); // Elementy unikalne
        }

        long long totalDuration = 0;

        // Wykonaj pomiary
        for(int m = 0; m < MEASUREMENTS_PER_POINT; ++m) {
            totalDuration += measure_time([&](){
                setA.difference(setB);
            });
        }

        double averageTime = static_cast<double>(totalDuration) / MEASUREMENTS_PER_POINT;
        outFile << currentSize << " " << averageTime << endl;

        cout << "[difference] Size: " << currentSize
             << " | Avg difference time: " << averageTime << " ns"
             << " | Overlap: " << overlapCount << "/" << currentSize << endl;
        if (averageTime > 2000000) {
            cout << "Time is too long" << endl;
            return;
        }
    }
}

int main() {

    //std::ofstream outFile1("time_insert.dat");
    //std::ofstream outFile2("time_remove.dat");
    //std::ofstream outFile3("time_sum.dat");
    //std::ofstream outFile4("time_inter.dat");
    //std::ofstream outFile5("time_contains.dat");
    std::ofstream outFile6("time_equals.dat");
    //std::ofstream outFile7("time_difference.dat");


    if ( !outFile6) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    //insertComplexity<SetHashed<int>>(outFile1);
    //removeComplexity<SetHashed<int>>(outFile2);
    //sumComplexity<SetHashed<int>>(outFile3);
    //intersectionComplexity<SetHashed<int>>(outFile4);
    //containsComplexity<SetHashed<int>>(outFile5);
    equalityComplexity<SetHashed<int>>(outFile6);
    //differenceComplexity<SetHashed<int>>(outFile7);

    //outFile1.close();
    //outFile2.close();
    //outFile3.close();
    //outFile4.close();
    //outFile5.close();
    outFile6.close();
    //outFile7.close();

    std::cout << "Done :)" << std::endl;
    return 0;
}