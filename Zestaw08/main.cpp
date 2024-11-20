#include "myqueue.h"

void test_push_pop() {
    std::cout << "Test: push i pop" << std::endl;
    MyQueue<int> q(5);

    // Test dodawania elementów
    q.push(10);
    q.push(20);
    q.push(30);
    assert(q.size() == 3);
    assert(q.front() == 10);
    assert(q.back() == 30);

    // Test usuwania elementów
    q.pop();
    assert(q.size() == 2);
    assert(q.front() == 20);
    q.pop();
    assert(q.size() == 1);
    assert(q.front() == 30);

    std::cout << "push i pop działają poprawnie!" << std::endl;
}

void test_full_empty() {
    std::cout << "Test: full i empty" << std::endl;
    MyQueue<int> q(3);

    assert(q.empty() == true);
    q.push(1);
    assert(q.empty() == false);
    q.push(2);
    q.push(3);
    assert(q.full() == true);

    q.pop();
    assert(q.full() == false);

    q.clear();
    assert(q.empty() == true);

    std::cout << "full i empty działają poprawnie!" << std::endl;
}

void test_clear() {
    std::cout << "Test: clear" << std::endl;
    MyQueue<int> q(5);
    q.push(100);
    q.push(200);
    q.push(300);

    assert(q.size() == 3);
    q.clear();
    assert(q.empty() == true);

    std::cout << "clear działa poprawnie!" << std::endl;
}

void test_copy_constructor() {
    std::cout << "Test: konstruktor kopiujący" << std::endl;
    MyQueue<std::string> q1(5);
    q1.push("A");
    q1.push("B");
    q1.push("C");

    MyQueue<std::string> q2(q1);
    assert(q2.size() == 3);
    assert(q2.front() == "A");
    assert(q2.back() == "C");

    q1.pop();
    assert(q1.front() == "B");
    assert(q2.front() == "A");

    std::cout << "konstruktor kopiujący działa poprawnie!" << std::endl;
}

void test_move_constructor() {
    std::cout << "Test: konstruktor przenoszący" << std::endl;
    MyQueue<int> q1(5);
    q1.push(10);
    q1.push(20);

    MyQueue<int> q2(std::move(q1));
    assert(q2.size() == 2);
    assert(q2.front() == 10);

    assert(q1.empty() == true); // Po przeniesieniu q1 powinien być pusty

    std::cout << "konstruktor przenoszący działa poprawnie!" << std::endl;
}

void test_assignment_operators() {
    std::cout << "Test: operatory przypisania" << std::endl;

    // Operator przypisania kopiujący
    MyQueue<int> q1(5);
    q1.push(1);
    q1.push(2);

    MyQueue<int> q2(10);
    q2 = q1;
    assert(q2.size() == 2);
    assert(q2.front() == 1);

    q1.pop();
    assert(q2.front() == 1); // Sprawdzenie, że q2 jest niezależne od q1

    // Operator przypisania przenoszący
    MyQueue<int> q3(5);
    q3 = std::move(q1);
    assert(q3.size() == 1); // Przeniesiony z q1
    assert(q3.front() == 2);

    assert(q1.empty() == true); // q1 powinien być pusty

    std::cout << "operatory przypisania działają poprawnie!" << std::endl;
}

void test_display() {
    std::cout << "Test: display" << std::endl;
    MyQueue<int> q(5);
    q.push(5);
    q.push(10);
    q.push(15);

    std::cout << "Zawartość kolejki: ";
    q.display(); // Oczekiwane: 5 10 15
    std::cout << std::endl;

    std::cout << "display działa poprawnie!" << std::endl;
}

int main() {
    try {
        test_push_pop();
        test_full_empty();
        test_clear();
        test_copy_constructor();
        test_move_constructor();
        test_assignment_operators();
        test_display();

        std::cout << "Wszystkie testy zakończone pomyślnie!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Błąd testu: " << e.what() << std::endl;
    }

    return 0;
}
