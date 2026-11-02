#include "avl.h"

static int maxInt(int a, int b) { 
    return a > b ? a : b; 
}

int AVLTree::h(AVLNode* n) { 
    return n ? n->height : 0; 
}

int AVLTree::balance(AVLNode* n) {
    return n ? h(n->left) - h(n->right) : 0; 
}

void AVLTree::update(AVLNode* n) { 
    if (n) n->height = 1 + maxInt(h(n->left), h(n->right)); 
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* middle = x->right;
    x->right = y; 
    y->left = middle;
    update(y); 
    update(x);
    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* middle = y->left;
    y->left = x; 
    x->right = middle;
    update(x); 
    update(y);
    return y;
}

AVLNode* AVLTree::insertNode(AVLNode* n, int key) {
    if (!n) {
        return new AVLNode(key);
    }
    if (key < n->key) {
        n->left = insertNode(n->left, key);
    }
    else if (key > n->key) {
        n->right = insertNode(n->right, key);
    }
    else return n;
    
    update(n);
    int b = balance(n);
    
    if (b > 1 && key < n->left->key) {
        return rotateRight(n);
    }
    if (b < -1 && key > n->right->key) {
        return rotateLeft(n);
    }
    if (b > 1 && key > n->left->key) {
        n->left = rotateLeft(n->left); 
        return rotateRight(n); 
    }
    if (b < -1 && key < n->right->key) { 
        n->right = rotateRight(n->right); 
        return rotateLeft(n); 
    }
    return n;
}

AVLNode* AVLTree::minNode(AVLNode* n) { 
    while (n && n->left) {
        n = n->left; 
    }
    return n; 
}

AVLNode* AVLTree::eraseNode(AVLNode* n, int key) {
    if (!n) { 
        return nullptr;
    }
    if (key < n->key) {
        n->left = eraseNode(n->left, key);
    }
    else if (key > n->key) {
        n->right = eraseNode(n->right, key);
    }
    else {
        if (!n->left || !n->right) {
            AVLNode* child = n->left ? n->left : n->right;
            delete n; 
            return child;
        }
        AVLNode* successor = minNode(n->right);
        n->key = successor->key;
        n->right = eraseNode(n->right, successor->key);
    }
    
    update(n);
    int b = balance(n);
    
    if (b > 1 && balance(n->left) >= 0) {
        return rotateRight(n);
    }
    if (b > 1 && balance(n->left) < 0) { 
        n->left = rotateLeft(n->left); 
        return rotateRight(n); 
    }
    if (b < -1 && balance(n->right) <= 0) {
        return rotateLeft(n);
    }
    if (b < -1 && balance(n->right) > 0) { 
        n->right = rotateRight(n->right); 
        return rotateLeft(n); 
    }
    return n;
}

bool AVLTree::containsNode(AVLNode* n, int key) {
    while (n) {
        if (key == n->key) return true;
        n = key < n->key ? n->left : n->right; 
    }
    return false;
}

long long AVLTree::sumNode(AVLNode* n) { 
    return n ? n->key + sumNode(n->left) + sumNode(n->right) : 0;
}

int AVLTree::countNode(AVLNode* n) { 
    return n ? 1 + countNode(n->left) + countNode(n->right) : 0; 
}

void AVLTree::inorderNode(AVLNode* n, int* a, int& i) {
    if (!n) return; 
    inorderNode(n->left, a, i); 
    a[i++] = n->key; 
    inorderNode(n->right, a, i);
}

void AVLTree::destroyNode(AVLNode* n) {
    if (!n) return; 
    destroyNode(n->left); 
    destroyNode(n->right); 
    delete n;
}

void AVLTree::printLevelsNode(AVLNode* root) {
    if (!root) { 
        std::cout << "(порожнє дерево)\nвисота: 0\n"; 
        return; 
    }
    int cap = countNode(root);
    AVLNode** q = new AVLNode*[cap];
    int* lev = new int[cap];
    int* parentId = new int[cap];
    const char** side = new const char*[cap];
    
    int front = 0, back = 0, idCounter = 0;
    q[back] = root; lev[back] = 1; parentId[back] = -1; side[back] = "-"; back++;

    std::cout << "вузол  рівень  батько  бік     ключ\n";
    while (front < back) {
        AVLNode* n = q[front];
        int l = lev[front];
        int p = parentId[front];
        const char* s = side[front];
        int curId = ++idCounter;
        front++;

        std::cout << curId << "\t" << l << "\t";
        if (p == -1) {
            std::cout << "-\t-\t";
        }
        else std::cout << p << "\t" << s << "\t";
        std::cout << n->key << "\n";

        if (n->left) { 
            q[back] = n->left; 
            lev[back] = l + 1; 
            parentId[back] = curId; 
            side[back] = "лівий"; 
            back++; 
        }
        if (n->right) { 
            q[back] = n->right; 
            lev[back] = l + 1; 
            parentId[back] = curId; 
            side[back] = "правий";
            back++; 
        }
    }
    std::cout << "висота: " << h(root) << "\n";
    delete[] q; 
    delete[] lev; 
    delete[] parentId; 
    delete[] side;
}

bool AVLTree::insert(int key) { 
    if (contains(key)) return false; 
    root = insertNode(root, key); 
    return true; 
}

bool AVLTree::contains(int key) const { 
    return containsNode(root, key); 
}

bool AVLTree::erase(int key) { 
    if (!contains(key)) {
        return false; 
    }
    root = eraseNode(root, key); 
    return true; 
}

long long AVLTree::sum() const { 
    return sumNode(root);
}

int AVLTree::height() const { 
    return h(root); 
}

int AVLTree::count() const { 
    return countNode(root); 
}

bool AVLTree::nth(int n, int& result) const {
    int c = countNode(root);
    if (n < 1 || n > c) {
        return false;
    }
    int* a = new int[c]; 
    int i = 0; 
    inorderNode(root, a, i);
    result = a[n - 1]; 
    delete[] a; 
    return true;
}

void AVLTree::printLevels() const { printLevelsNode(root); }
void AVLTree::clear() { destroyNode(root); root = nullptr; }
void AVLTree::exportKeys(int* output, int& c) const { c = 0; inorderNode(root, output, c); }