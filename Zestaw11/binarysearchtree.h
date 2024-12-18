#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <cassert>

template <typename T>
struct BSTNode {
    T value;
    BSTNode *left, *right;

    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() {
        delete left; delete right;
    }
};


// Szablon dla binarnego drzewa poszukiwań.
template <typename T>
class BinarySearchTree {
    BSTNode<T> *root;
public:
    BinarySearchTree() : root(nullptr) {} // konstruktor domyślny
    ~BinarySearchTree() {
        delete root;
    } // trzeba wyczyścić
    void clear() {
        delete root; root = nullptr;
    }
    bool empty() const {
        return root == nullptr;
    }
    T& top() {
        assert(root != nullptr); return root->value;
    } // podgląd korzenia
    void insert(const T& item) {
        root = insert(root, item);
    }


    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    T* iter_search(const T& item) const { // wg libavl
        for (auto node=root; node != nullptr; ) {
            if (item == node->value) {
                return &(node->value);
            } else if (item < node->value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return nullptr;
    }


    T* find_min() {
        if (root == nullptr) { // jeśli drzewo jest puste to zwracamy nullptr
            return nullptr;
        }
        BSTNode<T>* node = root;
        while (node->left != nullptr) {
            node = node->left;
        }
        return &(node->value); // zwracamy wskaźnik na najmniejsza wartość
    }


    T* find_max() {
        if (root == nullptr) { // jeśli drzewo jest puste to zwracamy nullptr
            return nullptr;
        }
        BSTNode<T>* node = root;
        while (node->right != nullptr) {
            node = node->right;
        }
        return &(node->value); // zwracamy wskaźnik na najwieksza wartość
    }


    void display() {
        display(root, 0);
    }


    void display(BSTNode<T>* node, int level) { // ze strony kursu
        if (node == nullptr) return;
        display(node->right, level + 1);
        for (int i = 0; i < level; i++) {
            std::cout << "   |";
        }
        std::cout << "---" << node->value << std::endl;
        display(node->left, level + 1);
    }


    BSTNode<T>* insert(BSTNode<T> *node, const T& item) {
        if (node == nullptr) {
            return new BSTNode<T>(item);
        }
        if (item < node->value) {
            node->left = insert(node->left, item);
        }
        else {
            node->right = insert(node->right, item);
        }
        return node; // zwraca nowy korzeń
    }
};


#endif //BINARYSEARCHTREE_H
