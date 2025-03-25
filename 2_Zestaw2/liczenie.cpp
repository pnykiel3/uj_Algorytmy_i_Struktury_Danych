#include <iostream>
#include <random>
#include <chrono>
#include <memory>
#include <fstream>
#include "setHashed.h"

#define NUM 800
#define MEASUREMENTS 1500.0
#define NUM_INITIAL_ELEMENTS 50 // Liczba początkowych elementów do zapełnienia zbioru
#define NUM_INCREMENTS 50        // Liczba kroków wzrostu rozmiaru zbioru
#define MEASUREMENTS_PER_STEP 1500 // Liczba pomiarów czasu wstawiania dla każdego kroku
#define MAX_VALUE 1000000         // Maksymalna wartość wstawianego elementu

using namespace std;
using namespace std::chrono;

template<typename Func>
long long measure_time(Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto stop = high_resolution_clock::now();
    return duration_cast<nanoseconds>(stop - start).count();
}

template<typename SetType>
void insertComplexityImproved(std::ofstream& outFile) {
    SetType mySet;
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> initial_dis(0, MAX_VALUE);

    // Krok 1: Wstępne zapełnienie zbioru unikalnymi elementami (warm-up i baza)
    for (int i = 0; i < NUM_INITIAL_ELEMENTS; ++i) {
        mySet.insert(initial_dis(gen));
    }

    // Krok 2: Mierzenie czasu wstawiania w miarę wzrostu rozmiaru zbioru
    for (int i = 0; i < NUM_INCREMENTS; ++i) {
        long long totalDuration = 0;
        std::vector<int> elements_to_insert(MEASUREMENTS_PER_STEP);
        std::uniform_int_distribution<> insert_dis(0, MAX_VALUE);

        // Generuj elementy do wstawienia przed pomiarem czasu
        for (int j = 0; j < MEASUREMENTS_PER_STEP; ++j) {
            elements_to_insert[j] = insert_dis(gen);
        }

        // Mierz czas wstawiania wielu losowych elementów
        for (int j = 0; j < MEASUREMENTS_PER_STEP; ++j) {
            int element = elements_to_insert[j];
            totalDuration += measure_time([&]() { mySet.insert(element); });
        }

        // Zapisz wyniki: aktualny rozmiar zbioru i średni czas wstawiania
        outFile << mySet.size() << " " << static_cast<double>(totalDuration) / MEASUREMENTS_PER_STEP << std::endl;

        // Dodaj trochę elementów do zbioru, aby zwiększyć jego rozmiar na następną iterację
        for (int k = 0; k < NUM_INITIAL_ELEMENTS / NUM_INCREMENTS; ++k) {
            mySet.insert(initial_dis(gen));
        }
    }
}



template<typename SetType>
void insertComplexity(ofstream& outFile) {
    SetType mySet;
    std::mt19937 gen(std::random_device{}());

    for (int i = 0; i < NUM; ++i) {
        std::uniform_int_distribution<> dis(0, (i > 0) ? i - 1 : 0);
        mySet.insert(dis(gen));

        long long totalDuration = 0;
        for (int j = 0; j < MEASUREMENTS; ++j) {
            totalDuration += measure_time([&]() { mySet.insert(dis(gen)); });
        }

        outFile << i << " " << static_cast<double>(totalDuration) / MEASUREMENTS << std::endl;
    }
}


template<typename SetType>
void removeComplexity(ofstream& outFile) {
    SetType mySet;
    std::mt19937 gen(std::random_device{}());

    for (int i = 0; i < NUM; ++i) {
        std::uniform_int_distribution<> dis(0, (i > 0) ? i - 1 : 0);
        mySet.insert(dis(gen));

        long long totalDuration = 0;
        for (int j = 0; j < MEASUREMENTS; ++j) {
            int num = dis(gen);
            mySet.insert(num);
            totalDuration += measure_time([&]() { mySet.remove(num); });
            mySet.insert(num);
        }

        outFile << i << " " << static_cast<double>(totalDuration) / MEASUREMENTS << std::endl;
    }
}


template<typename SetType>
void sumComplexity(ofstream& outFile) {
    SetType set1, set2;
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, NUM - 1);

    for (int i = 0; i < NUM; ++i) {
        set1.insert(dis(gen));
        set2.insert(dis(gen));

        long long totalDuration = 0;
        for (int j = 0; j < MEASUREMENTS; ++j) {
            totalDuration += measure_time([&]() { set1.sum(set2); });
        }

        outFile << i << " " << static_cast<double>(totalDuration) / MEASUREMENTS << std::endl;
    }
}

template<typename SetType>
void intersectionComplexity(ofstream& outFile) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, NUM - 1);

    for (int i = 0; i < NUM; ++i) {
        auto set1 = make_unique<SetType>();
        auto set2 = make_unique<SetType>();

        for (int j = 0; j < i; ++j) {
            int num = dis(gen);
            set1->insert(num);
            set2->insert(num);
        }

        long long totalDuration = 0;
        for (int j = 0; j < MEASUREMENTS; ++j) {
            totalDuration += measure_time([&]() { set1->intersection(*set2); });
        }

        outFile << i << " " << static_cast<double>(totalDuration) / MEASUREMENTS << std::endl;
    }
}

template<typename SetType>
void containsComplexity(ofstream& outFile) {
    SetType mySet;
    std::mt19937 gen(std::random_device{}());

    for (int i = 0; i < NUM; ++i) {
        std::uniform_int_distribution<> dis(0, (i > 0) ? i - 1 : 0);
        mySet.insert(dis(gen));

        long long totalDuration = 0;
        for (int j = 0; j < MEASUREMENTS; ++j) {
            totalDuration += measure_time([&]() { mySet.contains(dis(gen)); });
        }

        outFile << i << " " << static_cast<double>(totalDuration) / MEASUREMENTS << std::endl;
    }
}


template<typename SetType>
void equalityComplexity(ofstream& outFile) {
    SetType set1, set2;
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, NUM - 1);

    for (int i = 0; i < NUM; ++i) {
        set1.insert(dis(gen));
        set2.insert(dis(gen));

        long long totalDuration = 0;
        for (int j = 0; j < MEASUREMENTS; ++j) {
            totalDuration += measure_time([&]() { set1.equals(set2); });
        }

        outFile << i << " " << static_cast<double>(totalDuration) / MEASUREMENTS << std::endl;
    }
}

template<typename SetType>
void differenceComplexity(ofstream& outFile) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, NUM - 1);

    for (int i = 0; i < NUM; ++i) {
        auto set1 = make_unique<SetType>();
        auto set2 = make_unique<SetType>();

        for (int j = 0; j < i; ++j) {
            int num = dis(gen);
            set1->insert(num);
            set2->insert(num);
        }

        long long totalDuration = 0;
        for (int j = 0; j < MEASUREMENTS; ++j) {
            totalDuration += measure_time([&]() { set1->difference(*set2); });
        }

        outFile << i << " " << static_cast<double>(totalDuration) / MEASUREMENTS << std::endl;
    }
}



int main() {
/*
    std::ofstream outFile1("time_insert.dat");
    std::ofstream outFile2("time_remove.dat");
    std::ofstream outFile3("time_sum.dat");
    std::ofstream outFile4("time_inter.dat");
    std::ofstream outFile5("time_contains.dat");
    std::ofstream outFile6("time_equals.dat");
    std::ofstream outFile7("time_difference.dat");


    if (!outFile1 || !outFile2 || !outFile3 || !outFile4 || !outFile5 || !outFile6 || !outFile7) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    insertComplexity<SetHashed<int>>(outFile1);
    removeComplexity<SetHashed<int>>(outFile2);
    sumComplexity<SetHashed<int>>(outFile3);
    intersectionComplexity<SetHashed<int>>(outFile4);
    containsComplexity<SetHashed<int>>(outFile5);
    equalityComplexity<SetHashed<int>>(outFile6);
    differenceComplexity<SetHashed<int>>(outFile7);

    outFile1.close();
    outFile2.close();
    outFile3.close();
    outFile4.close();
    outFile5.close();
    outFile6.close();
    outFile7.close();
*/
    ofstream o1("insert_old.dat");
    ofstream o2("insert_new.dat");
    insertComplexity<SetHashed<int>>(o1);
    insertComplexityImproved<SetHashed<int>>(o2);
    o1.close();
    o2.close();
    std::cout << "Done :)" << std::endl;
    return 0;
}