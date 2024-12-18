#include "binarysearchtree.h"

void test1() {
    std::cout << "Test1:\t";
    BinarySearchTree<int> tree;

    tree.insert(14);
    tree.insert(8);
    tree.insert(2);
    tree.insert(58);
    tree.insert(16);
    tree.insert(10);
    tree.insert(47);
    assert(tree.top() == 14);
    assert(*tree.find_min() == 2);
    assert(*tree.find_max() == 58);
    tree.clear();
    assert(tree.empty());
    std::cout << "[[poprawny]]" << std::endl;
}

void test2() {
    std::cout << "Test2:\t";
    BinarySearchTree<int> tree;

    tree.insert(60);
    tree.insert(49);
    tree.insert(47);
    tree.insert(8);
    tree.insert(16);
    tree.insert(55);
    tree.insert(69);
    tree.insert(420);
    tree.insert(220);
    tree.insert(65);
    tree.insert(777);
    assert(*tree.find_min() == 8);
    assert(*tree.find_max() == 777);
    std::cout << "[[poprawny]]" << std::endl;
}

void test3() {
    std::cout << "Test3:\t";
    BinarySearchTree<int> tree;

    tree.insert(5);
    tree.insert(10);
    tree.insert(15);
    tree.insert(798);
    tree.insert(12);
    tree.insert(234);
    tree.insert(3);
    tree.insert(987);
    tree.insert(1);
    tree.insert(44);
    assert(*tree.find_min() == 1);
    assert(*tree.find_max() == 987);
    std::cout << "[[poprawny]]" << std::endl;
}

void test4() {
    std::cout << "Test4:\t";
    BinarySearchTree<int> tree;

    tree.insert(50);
    tree.insert(10);
    tree.insert(31);
    tree.insert(34);
    tree.insert(22);
    tree.insert(7);
    tree.insert(8);
    tree.insert(1);
    tree.insert(151);
    tree.insert(69);
    tree.insert(777);
    tree.insert(90);
    tree.insert(62);
    tree.insert(502);
    tree.insert(1001);
    assert(*tree.find_min() == 1);
    assert(*tree.find_max() == 1001);
    std::cout << "[[poprawny]]" << std::endl;
}

void test5() {
    std::cout << "Test5:\t";
    BinarySearchTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    assert(*tree.find_min() == 1);
    assert(*tree.find_max() == 10);
    std::cout << "[[poprawny]]" << std::endl;
}

void test6() {
    std::cout << "Test6:\t";
    BinarySearchTree<int> tree;

    tree.insert(61);
    tree.insert(41);
    tree.insert(73);
    tree.insert(37);
    tree.insert(13);
    tree.insert(59);
    tree.insert(19);
    tree.insert(97);
    tree.insert(83);
    tree.insert(5);
    assert(*tree.find_min() == 5);
    assert(*tree.find_max() == 97);
    std::cout << "[[poprawny]]" << std::endl;
}

int main() {
    try {
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        std::cout << "Wszystkie testy zakończone pomyślnie!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Błąd testu: " << e.what() << std::endl;
    }
    return 0;
}
