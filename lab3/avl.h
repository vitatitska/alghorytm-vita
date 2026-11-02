#ifndef AVL_H
#define AVL_H
#include <iostream>

struct AVLNode {
    int key, height;
    AVLNode *left, *right;
    explicit AVLNode(int value) : key(value), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
    AVLNode* root;
    static int h(AVLNode* n);
    static int balance(AVLNode* n);
    static void update(AVLNode* n);
    static AVLNode* rotateRight(AVLNode* y);
    static AVLNode* rotateLeft(AVLNode* x);
    static AVLNode* insertNode(AVLNode* n, int key);
    static AVLNode* eraseNode(AVLNode* n, int key);
    static AVLNode* minNode(AVLNode* n);
    static bool containsNode(AVLNode* n, int key);
    static long long sumNode(AVLNode* n);
    static int countNode(AVLNode* n);
    static void inorderNode(AVLNode* n, int* a, int& i);
    static void destroyNode(AVLNode* n);
    static void printLevelsNode(AVLNode* root);
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { clear(); }
    bool insert(int key);
    bool contains(int key) const;
    bool erase(int key);
    long long sum() const;
    int height() const;
    int count() const;
    bool nth(int n, int& result) const;
    void printLevels() const;
    void clear();
    void exportKeys(int* output, int& c) const;
};
#endif
