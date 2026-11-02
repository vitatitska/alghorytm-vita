#ifndef RED_BLACK_H
#define RED_BLACK_H
#include <iostream>

class RedBlackTree {
    struct Node {
        int key;
        bool red;
        Node *left, *right;
        explicit Node(int k) : key(k), red(true), left(nullptr), right(nullptr) {}
    };
    Node* root;
    static bool isRed(Node* n);
    static Node* rotateLeft(Node* h);
    static Node* rotateRight(Node* h);
    static void flipColors(Node* h);
    static Node* insertNode(Node* h, int key);
    static int countNode(Node* n);
    static int heightNode(Node* n);
    static void destroyNode(Node* n);
    static void printLevelsNode(Node* root);
public:
    RedBlackTree() : root(nullptr) {}
    ~RedBlackTree() { clear(); }
    void insert(int key);
    int height() const;
    void printLevels() const;
    void clear();
};
#endif
