#include "mypriorityqueue.h"
#include <cassert>

void test_push_pop() {
    std::cout << "Test: push i pop" << std::endl;
    MyPriorityQueue<int> pq;

    // Test dodawania elementów
    pq.push(10);
    pq.push(20);
    pq.push(30);
    assert(pq.size() == 3);
    assert(pq.top() == 30);

    // Test usuwania elementów
    pq.pop();
    assert(pq.size() == 2);
    assert(pq.top() == 20);
    pq.pop();
    assert(pq.size() == 1);
    assert(pq.top() == 10);

    std::cout << "push i pop działają poprawnie!" << std::endl;
}

void test_empty() {
    std::cout << "Test: empty" << std::endl;
    MyPriorityQueue<int> pq;
    assert(pq.empty());

    pq.push(1);
    assert(pq.empty() == false);

    pq.pop();
    assert(pq.empty());

    std::cout << "empty działa poprawnie!" << std::endl;
}

void test_clear() {
    std::cout << "Test: clear" << std::endl;
    MyPriorityQueue<int> pq;
    pq.push(100);
    pq.push(200);
    pq.push(300);

    assert(pq.size() == 3);
    pq.clear();
    assert(pq.empty());

    std::cout << "clear działa poprawnie!" << std::endl;
}

void test_top_exception() {
    std::cout << "Test: wyjątek dla top" << std::endl;
    MyPriorityQueue<int> pq;

    try {
        pq.top();
        assert(false); // Jeśli dotrzemy tutaj, test nie przeszedł
    } catch (const std::runtime_error& e) {
        std::cout << "Wyjątek poprawnie zgłoszony: " << e.what() << std::endl;
    }
}

void test_pop_exception() {
    std::cout << "Test: wyjątek dla pop" << std::endl;
    MyPriorityQueue<int> pq;

    try {
        pq.pop();
        assert(false); // Jeśli dotrzemy tutaj, test nie przeszedł
    } catch (const std::runtime_error& e) {
        std::cout << "Wyjątek poprawnie zgłoszony: " << e.what() << std::endl;
    }
}

void test_assignment_operators() {
    std::cout << "Test: operatory przypisania" << std::endl;

    // Operator przypisania kopiujący
    MyPriorityQueue<int> pq1;
    pq1.push(10);
    pq1.push(20);

    MyPriorityQueue<int> pq2;
    pq2 = pq1;
    assert(pq2.size() == 2);
    assert(pq2.top() == 20);

    pq1.pop();
    assert(pq2.top() == 20); // Sprawdzenie niezależności pq1 i pq2

    // Operator przypisania przenoszący
    MyPriorityQueue<int> pq3;
    pq3 = std::move(pq1);
    assert(pq3.size() == 1); // Przeniesiony z pq1
    assert(pq3.top() == 10);

    assert(pq1.empty()); // pq1 powinien być pusty

    std::cout << "operatory przypisania działają poprawnie!" << std::endl;
}

void test_display() {
    std::cout << "Test: display" << std::endl;
    MyPriorityQueue<int> pq;
    pq.push(15);
    pq.push(25);
    pq.push(5);

    std::cout << "Zawartość kolejki: ";
    pq.display(); // Oczekiwane: 15 25 5
    std::cout << std::endl;

    std::cout << "display działa poprawnie!" << std::endl;
}

int main() {
    try {
        test_push_pop();
        test_empty();
        test_clear();
        test_top_exception();
        test_pop_exception();
        test_assignment_operators();
        test_display();

        std::cout << "Wszystkie testy zakończone pomyślnie!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Błąd testu: " << e.what() << std::endl;
    }

    return 0;
}
