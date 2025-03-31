#ifndef PRIORITYQUEUEBINARY_H
#define PRIORITYQUEUEBINARY_H


const int MAX_SIZE = 1000000; // maksymalna liczba elementów w kopcu

class BinaryHeap {
private:
    int items[MAX_SIZE + 1]; // indeks 0 nie jest używany
    int currentSize;         // liczba elementów w kopcu

    // Pomocnicza metoda przesiewania w dół od indeksu i
    void percolate_down(int i) {
        while(i * 2 <= currentSize) {
            // Debug: wypisanie stanu kopca przed zmianami (opcjonalnie)
            // std::cout << "before percolate_down: "; printHeap();
            int mc = min_child(i);
            if(items[i] > items[mc]) {
                int temp = items[i];
                items[i] = items[mc];
                items[mc] = temp;
            }
            i = mc;
            // Debug: wypisanie stanu kopca po zamianie (opcjonalnie)
            // std::cout << "after percolate_down: "; printHeap();
        }
    }

    // Zwraca indeks dziecka o mniejszej wartości
    int min_child(int i) const {
        if(i * 2 + 1 > currentSize) { // brak prawego dziecka
            return i * 2;
        }
        if(items[i * 2] < items[i * 2 + 1]) {
            return i * 2;
        }
        return i * 2 + 1;
    }

    // Pomocnicza metoda przesiewania w górę
    void percolate_up() {
        int i = currentSize;
        while(i / 2 > 0) {
            // Debug: wypisanie stanu kopca przed zmianami (opcjonalnie)
            // std::cout << "before percolate_up: "; printHeap();
            if(items[i] < items[i / 2]) {
                int temp = items[i];
                items[i] = items[i / 2];
                items[i / 2] = temp;
            }
            i = i / 2;
            // Debug: wypisanie stanu kopca po zamianie (opcjonalnie)
            // std::cout << "after percolate_up: "; printHeap();
        }
    }

public:
    BinaryHeap() : currentSize(0) {
        items[0] = 0; // element zerowy nie jest używany
    }

    // Wstawia nowy element do kopca
    void insert(int priority) {
        if(currentSize >= MAX_SIZE) {
            std::cout << "Kopiec jest pełny!" << std::endl;
            return;
        }
        currentSize++;
        items[currentSize] = priority;
        percolate_up();
    }

    // Buduje kopiec z podanej tablicy (przekazujemy tablicę oraz liczbę elementów)
    void build_heap(const int arr[], int n) {
        if(n > MAX_SIZE) {
            std::cout << "Za dużo elementów do kopca!" << std::endl;
            return;
        }
        // Skopiuj elementy do tablicy kopca (od indeksu 1)
        for (int i = 0; i < n; i++) {
            items[i + 1] = arr[i];
        }
        currentSize = n;
        // Przesiewamy w dół od ostatniego rodzica
        for (int i = currentSize / 2; i > 0; i--) {
            percolate_down(i);
        }
    }

    // Zwraca najmniejszy element (korzeń)
    int find_min() const {
        if(currentSize == 0) {
            std::cout << "Kopiec jest pusty!" << std::endl;
            return -1; // lub wartość sygnalizująca błąd
        }
        return items[1];
    }

    // Usuwa i zwraca najmniejszy element z kopca
    int del_min() {
        if(currentSize == 0) {
            std::cout << "Kopiec jest pusty!" << std::endl;
            return -1;
        }
        int return_value = items[1];
        items[1] = items[currentSize];
        currentSize--;
        percolate_down(1);
        return return_value;
    }

    // Sprawdza, czy kopiec jest pusty
    bool is_empty() const {
        return currentSize == 0;
    }

    // Zwraca liczbę elementów w kopcu
    int size() const {
        return currentSize;
    }

    // Pomocnicza metoda do wypisywania zawartości kopca (od indeksu 1 do currentSize)
    void printHeap() const {
        for (int i = 1; i <= currentSize; i++) {
            std::cout << items[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif