#include <iostream>
#include <random>
#include <chrono>
#include <memory>
#include <fstream>
#include "setlinked.h"
#include "setsimple.h"
#include "dictionarysimple.h"

#define NUM 750
#define MEASUREMENTS 500.0
using namespace std;
using namespace std::chrono;

template<typename Func>
long long measure_time(Func func) {
    auto beg = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - beg).count();
}

template<typename SetType>
void showInsertComplexity(ofstream& outFile) {
    SetType mySet;
    std::mt19937 gen(std::random_device{}());

    for (int i = 0; i < NUM; ++i) {
        std::uniform_int_distribution<> dis(0, (i > 0) ? i - 1 : 0);
        mySet.insert(dis(gen));

        long long totalDuration = 0;
        for (int j = 0; j < MEASUREMENTS; ++j) {
            totalDuration += measure_time([&]() { mySet.insert(dis(gen)); });
        }

        outFile << i << " " << totalDuration / MEASUREMENTS << std::endl;
    }
}


void DshowInsertCOmplexity(ofstream& outFile) {
      dictionarysimple mySet;
    std::mt19937 gen(std::random_device{}());

    for (int i = 0; i < NUM; ++i) {
        std::uniform_int_distribution<> dis(0, (i > 0) ? i - 1 : 0);
        mySet.insert(std::to_string(dis(gen)));

        long long totalDuration = 0;
        for (int j = 0; j < MEASUREMENTS; ++j) {
            totalDuration += measure_time([&]() { mySet.insert(std::to_string(dis(gen))); });
        }

        outFile << i << " " << totalDuration / MEASUREMENTS << std::endl;
    }

  }

template<typename SetType>
void showRemoveComplexity(ofstream& outFile) {
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

        outFile << i << " " << totalDuration / MEASUREMENTS << std::endl;
    }
}

void DshowRemoveComplexity(ofstream& outFile) {
    dictionarysimple mySet;
    std::mt19937 gen(std::random_device{}());

    for (int i = 0; i < NUM; ++i) {
        std::uniform_int_distribution<> dis(0, (i > 0) ? i - 1 : 0);
        mySet.insert(std::to_string(dis(gen)));

        long long totalDuration = 0;
        for (int j = 0; j < MEASUREMENTS; ++j) {
            string num = (std::to_string(dis(gen)));
            mySet.insert(num);
            totalDuration += measure_time([&]() { mySet.remove(num); });
            mySet.insert(num);
        }

        outFile << i << " " << totalDuration / MEASUREMENTS << std::endl;
    }
}

template<typename SetType>
void showSumComplexity(ofstream& outFile) {
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

        outFile << i << " " << totalDuration / MEASUREMENTS << std::endl;
    }
}

template<typename SetType>
void showIntersectionComplexity(ofstream& outFile) {
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

        outFile << i << " " << totalDuration / MEASUREMENTS << std::endl;
    }
}

template<typename SetType>
void showContainsComplexity(ofstream& outFile) {
    SetType mySet;
    std::mt19937 gen(std::random_device{}());

    for (int i = 0; i < NUM; ++i) {
        std::uniform_int_distribution<> dis(0, (i > 0) ? i - 1 : 0);
        mySet.insert(dis(gen));

        long long totalDuration = 0;
        for (int j = 0; j < MEASUREMENTS; ++j) {
            totalDuration += measure_time([&]() { mySet.exists(dis(gen)); });
        }

        outFile << i << " " << totalDuration / MEASUREMENTS << std::endl;
    }
}

void DshowContainsComplexity(ofstream& outFile) {
    dictionarysimple mySet;
    std::mt19937 gen(std::random_device{}());

    for (int i = 0; i < NUM; ++i) {
        std::uniform_int_distribution<> dis(0, (i > 0) ? i - 1 : 0);
        mySet.insert(std::to_string(dis(gen)));

        long long totalDuration = 0;
        for (int j = 0; j < MEASUREMENTS; ++j) {
            totalDuration += measure_time([&]() { mySet.exists(std::to_string(dis(gen))); });
        }

        outFile << i << " " << totalDuration / MEASUREMENTS << std::endl;
    }
}

template<typename SetType>
void showEqualityComplexity(ofstream& outFile) {
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

        outFile << i << " " << totalDuration / MEASUREMENTS << std::endl;
    }
}

template<typename SetType>
void showDifferenceComplexity(ofstream& outFile) {
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
            totalDuration += measure_time([&]() { set1->complement(*set2); });
        }

        outFile << i << " " << totalDuration / MEASUREMENTS << std::endl;
    }
}



int main() {
    int choice;
    std::ofstream outFileSS("timeSS.dat");
    std::ofstream outFileSL("timeSL.dat");
    std::ofstream outFileD("timeD.dat");
    if (!outFileSS|| !outFileSL || !outFileD) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::cout << "Select operation to test:" << std::endl;
    std::cout << "1. Insert Complexity" << std::endl;
    std::cout << "2. Remove Complexity" << std::endl;
    std::cout << "3. Sum Complexity" << std::endl;
    std::cout << "4. Intersection Complexity" << std::endl;
    std::cout << "5. Contains Complexity" << std::endl;
    std::cout << "6. Equals Complexity" << std::endl;
    std::cout << "7. Difference Complexity "<< std::endl;
    std::cout << "Enter choice (1-7): ";
    std::cin >> choice;

      switch(choice){
        case 1: {
          showInsertComplexity<setLinked>(outFileSL);
          showInsertComplexity<setSimple>(outFileSS);
          DshowInsertCOmplexity(outFileD);
          break;
          }
        case 2: {
          showRemoveComplexity<setLinked>(outFileSL);
          showRemoveComplexity<setSimple>(outFileSS);
          DshowRemoveComplexity(outFileD);
          break;
          }
        case 3: {
          showSumComplexity<setLinked>(outFileSL);
            showSumComplexity<setSimple>(outFileSS);
            break;
          }
        case 4: {
 			showIntersectionComplexity<setLinked>(outFileSL);
            showIntersectionComplexity<setSimple>(outFileSS);
            break;
          }
        case 5: {
            showContainsComplexity<setLinked>(outFileSL);
            showContainsComplexity<setSimple>(outFileSS);
            DshowContainsComplexity(outFileD);
            break;
            }
        case 6: {
            showEqualityComplexity<setLinked>(outFileSL);
            showEqualityComplexity<setSimple>(outFileSS);
            break;
            }
        case 7: {
            showDifferenceComplexity<setLinked>(outFileSL);
            showDifferenceComplexity<setSimple>(outFileSS);
            break;
        default: std::cout << "Invalid choice!" << std::endl;
    	}
    }

    outFileSS.close();
    std::cout << "Done :)" << std::endl;
    return 0;
}