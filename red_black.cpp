#include "red_black.h"

static int maxVal(int a, int b) { return a > b ? a : b; }

bool RedBlackTree::isRed(Node* n) { return n && n->red; }
RedBlackTree::Node* RedBlackTree::rotateLeft(Node* h) {
    Node* x = h->right; h->right = x->left; x->left = h;
    x->red = h->red; h->red = true; return x;
}
RedBlackTree::Node* RedBlackTree::rotateRight(Node* h) {
    Node* x = h->left; h->left = x->right; x->right = h;
    x->red = h->red; h->red = true; return x;
}
void RedBlackTree::flipColors(Node* h) {
    h->red = !h->red;
    if(h->left) h->left->red = !h->left->red;
    if(h->right) h->right->red = !h->right->red;
}
RedBlackTree::Node* RedBlackTree::insertNode(Node* h, int key) {
    if(!h) return new Node(key);
    if(key < h->key) h->left = insertNode(h->left, key);
    else if(key > h->key) h->right = insertNode(h->right, key);
    
    if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
    if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
    if (isRed(h->left) && isRed(h->right)) flipColors(h);
    return h;
}
int RedBlackTree::countNode(Node* n) { return n ? 1 + countNode(n->left) + countNode(n->right) : 0; }
int RedBlackTree::heightNode(Node* n) { return n ? 1 + maxVal(heightNode(n->left), heightNode(n->right)) : 0; }
void RedBlackTree::destroyNode(Node* n) { if(!n) return; destroyNode(n->left); destroyNode(n->right); delete n; }

// Друк згідно з прикладом виводу методички: вузол, рівень, батько, бік, ключ, колір
void RedBlackTree::printLevelsNode(Node* root) {
    if(!root) { std::cout << "(порожнє дерево)\nвисота: 0\n"; return; }
    int cap = countNode(root);
    Node** q = new Node*[cap];
    int* lev = new int[cap];
    int* parentId = new int[cap];
    const char** side = new const char*[cap];
    
    int front = 0, back = 0, idCounter = 0;
    q[back] = root; lev[back] = 1; parentId[back] = -1; side[back] = "-"; back++;

    std::cout << "вузол  рівень  батько  бік     ключ    колір\n";
    while (front < back) {
        Node* n = q[front];
        int l = lev[front];
        int p = parentId[front];
        const char* s = side[front];
        int curId = ++idCounter;
        front++;

        std::cout << curId << "\t" << l << "\t";
        if (p == -1) std::cout << "-\t-\t";
        else std::cout << p << "\t" << s << "\t";
        
        std::cout << n->key << "\t" << (n->red ? "червоний" : "чорний") << "\n";

        if (n->left) { q[back] = n->left; lev[back] = l + 1; parentId[back] = curId; side[back] = "лівий"; back++; }
        if (n->right) { q[back] = n->right; lev[back] = l + 1; parentId[back] = curId; side[back] = "правий"; back++; }
    }
    std::cout << "висота: " << heightNode(root) << "\n";
    delete[] q; delete[] lev; delete[] parentId; delete[] side;
}

void RedBlackTree::insert(int key) { root = insertNode(root, key); if(root) root->red = false; }
int RedBlackTree::height() const { return heightNode(root); }
void RedBlackTree::printLevels() const { printLevelsNode(root); }
void RedBlackTree::clear() { destroyNode(root); root = nullptr; }