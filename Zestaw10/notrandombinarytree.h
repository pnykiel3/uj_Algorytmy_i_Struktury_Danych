#ifndef NOTRANDOMBINARYTREE_H
#define NOTRANDOMBINARYTREE_H

#include <iostream>
#include <cassert>
#include <queue>

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


// Szablon dla przypadkowego drzewa binarnego.
template <typename T>
class notrandombinarytree {
    BSTNode<T> *root;
public:
    notrandombinarytree() : root(nullptr) {} // konstruktor domyślny
    ~notrandombinarytree() { delete root; } // trzeba wyczyścić (rekurencyjnie)
    void clear() { delete root; root = nullptr; }
    bool empty() const { return root == nullptr; }
    T& top() { assert(root != nullptr); return root->value; } // podgląd korzenia
    void insert(const T& item) { root = insert(root, item); }
    int calc_leaves_r() { return calc_leaves_r(root); }
    int calc_leaves_i() { return calc_leaves_i(root); }

    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    void display() { display(root, 0); }
    virtual void visit(BSTNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
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

    void display(BSTNode<T> *node, int level) {
        if (node == nullptr) return;
        display(node->right, level + 1);
        for (int i = 0; i < level; i++) {
            std::cout << "   |";
        }
        std::cout << "---" << node->value << std::endl;
        display(node->left, level + 1);
    }

    int calc_leaves_r(BSTNode<T>* node) {

        if (node == nullptr) {
            return 0;
        }
        if (node ->left == nullptr && node->right == nullptr) {
            return 1;
        }
        return calc_leaves_r(node->left) + calc_leaves_r(node->right);
    }


    int calc_leaves_i(BSTNode<T>* node) {

        if (node == nullptr) {
            return 0;
        }

        std::queue <BSTNode<T>*> q;
        int leaves = 0;
        q.push(node);

        while (!q.empty()) {

            BSTNode<T>* current = q.front();
            q.pop();


            if ( current -> left == nullptr && current -> right == nullptr) {
                leaves++;
            } else {
                if (current -> left != nullptr) {
                    q.push(current->left);
                }
                if (current -> right != nullptr) {
                    q.push(current->right);
                }
            }
        }
        return leaves;
    }
};


#endif //NOTRANDOMBINARYTREE_H
