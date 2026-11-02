#include "two_three.h"

bool TwoThreeTree::containsNode(TwoThreeNode* n, int key) {
    while (n) {
        if (key == n->keys[0] || (n->count == 2 && key == n->keys[1])) {
            return true;
        }
        if (key < n->keys[0]) {
            n = n->child[0];
        } 
        else if (n->count == 1 || key < n->keys[1]) {
            n = n->child[1];
        }
        else {
            n = n->child[2];
        }
    }
    return false;
}

TwoThreeTree::Promotion TwoThreeTree::insertRec(TwoThreeNode* n, int key) {
    Promotion none{false, 0, nullptr};
    if (n->leaf()) {
        if (n->count == 1) {
            if (key < n->keys[0]) {
                n->keys[1] = n->keys[0]; 
                n->keys[0] = key; 
            }
            else {
                n->keys[1] = key;
            }
            n->count = 2; 
            return none;
        }
        int vals[3] = { n->keys[0], n->keys[1], key };
        for(int i = 0; i < 3; i++) {
            for(int j = i + 1; j < 3; j++) {
                if(vals[j] < vals[i]) { 
                    int t = vals[i]; 
                    vals[i] = vals[j]; 
                    vals[j] = t; 
                }
            }
        }
        
        n->keys[0] = vals[0]; 
        n->count = 1;
        TwoThreeNode* right = new TwoThreeNode(); 
        right->keys[0] = vals[2]; 
        right->count = 1;
        return Promotion{ true, vals[1], right };
    }
    
    int slot = (key < n->keys[0]) ? 0 : ((n->count == 1 || key < n->keys[1]) ? 1 : 2);
    Promotion p = insertRec(n->child[slot], key);
    if (!p.split) return none;
    
    if (n->count == 1) {
        if (slot == 0) {
            n->keys[1] = n->keys[0]; 
            n->keys[0] = p.key;
            n->child[2] = n->child[1]; 
            n->child[1] = p.right;
        } else {
            n->keys[1] = p.key; 
            n->child[2] = p.right;
        }
        n->count = 2; 
        return none;
    }
    
    int vals[3]; 
    TwoThreeNode* kids[4];
    if(slot == 0){ 
        vals[0]=p.key; vals[1]=n->keys[0]; vals[2]=n->keys[1]; 
        kids[0]=n->child[0]; kids[1]=p.right; kids[2]=n->child[1]; kids[3]=n->child[2]; 
    }
    else if(slot == 1){ 
        vals[0]=n->keys[0]; vals[1]=p.key; vals[2]=n->keys[1]; 
        kids[0]=n->child[0]; kids[1]=n->child[1]; kids[2]=p.right; kids[3]=n->child[2]; 
    }
    else { 
        vals[0]=n->keys[0]; vals[1]=n->keys[1]; vals[2]=p.key; 
        kids[0]=n->child[0]; kids[1]=n->child[1]; kids[2]=n->child[2]; kids[3]=p.right; 
    }
    
    n->keys[0] = vals[0]; 
    n->count = 1; 
    n->child[0] = kids[0]; 
    n->child[1] = kids[1]; 
    n->child[2] = nullptr;
    
    TwoThreeNode* right = new TwoThreeNode(); 
    right->keys[0] = vals[2]; 
    right->count = 1; 
    right->child[0] = kids[2]; 
    right->child[1] = kids[3];
    
    return Promotion{ true, vals[1], right };
}

void TwoThreeTree::collect(TwoThreeNode* n, int* a, int& i) {
    if(!n) return;
    if(n->count == 1){ 
        collect(n->child[0], a, i); 
        a[i++] = n->keys[0]; 
        collect(n->child[1], a, i); 
    }
    else { 
        collect(n->child[0], a, i); 
        a[i++] = n->keys[0]; 
        collect(n->child[1], a, i); 
        a[i++] = n->keys[1]; 
        collect(n->child[2], a, i); 
    }
}

int TwoThreeTree::countKeysNode(TwoThreeNode* n) {
    if (!n) return 0;
    int c = n->count;
    for (int i = 0; i <= n->count; ++i) {
        c += countKeysNode(n->child[i]);
    }
    return c;
}

void TwoThreeTree::destroyNode(TwoThreeNode* n) {
    if(!n) return;
    for(int i = 0; i < 3; i++) {
        destroyNode(n->child[i]); 
    }
    delete n;
}

int TwoThreeTree::heightNode(TwoThreeNode* n) {
    if(!n) return 0;
    return 1 + heightNode(n->child[0]);
}

void TwoThreeTree::printLevelsNode(TwoThreeNode* root) {
    if(!root){ 
        std::cout << "(порожнє дерево)\nвисота: 0\n"; 
        return; 
    }
    
    int cap = 2000;
    TwoThreeNode** q = new TwoThreeNode*[cap]; 
    int* lev = new int[cap]; 
    int* parentId = new int[cap]; 
    int* childNo = new int[cap];
    
    int front = 0, back = 0, idCounter = 0;
    q[back] = root; 
    lev[back] = 1; 
    parentId[back] = -1; 
    childNo[back++] = 0;
    
    std::cout << "вузол  рівень  батько  нащадок  ключі\n";
    while(front < back) {
        TwoThreeNode* n = q[front];
        int l = lev[front];
        int p = parentId[front];
        int c = childNo[front];
        int curId = ++idCounter;
        front++;
        
        std::cout << curId << "\t" << l << "\t";
        if (p == -1) {
             std::cout << "-\t-\t";
        }
        else {
            std::cout << p << "\t" << c << "\t";
        }
        
        if (n->count == 1) {
            std::cout << n->keys[0] << "\n";
        }
        else {
            std::cout << n->keys[0] << " " << n->keys[1] << "\n";
        }
        
        for(int j = 0; j <= n->count; j++) {
            if(n->child[j]) {
                q[back] = n->child[j]; 
                lev[back] = l + 1; 
                parentId[back] = curId; 
                childNo[back] = j + 1; 
                back++;
            }
        }
    }
    std::cout << "висота: " << heightNode(root) << "\n";
    delete[] q; 
    delete[] lev; 
    delete[] parentId; 
    delete[] childNo;
}

bool TwoThreeTree::insert(int key) {
    if(contains(key)) return false;
    if(!root){ 
        root = new TwoThreeNode(); 
        root->keys[0] = key; 
        root->count = 1; 
        return true; 
    }
    Promotion p = insertRec(root, key);
    if(p.split){ 
        TwoThreeNode* nr = new TwoThreeNode(); 
        nr->keys[0] = p.key; 
        nr->count = 1; 
        nr->child[0] = root; 
        nr->child[1] = p.right; 
        root = nr; 
    }
    return true;
}

bool TwoThreeTree::contains(int key) const { return containsNode(root, key); }
int TwoThreeTree::keyCount() const { return countKeysNode(root); }

bool TwoThreeTree::erase(int key) {
    if(!contains(key)) return false;
    int kCount = keyCount();
    int* all = new int[kCount];
    int n = 0; 
    collect(root, all, n);
    clear();
    for(int i = 0; i < n; i++) {
        if(all[i] != key) {
             insert(all[i]);
        }
    }
    delete[] all; 
    return true;
}

long long TwoThreeTree::sum() const {
    int kCount = keyCount();
    if (kCount == 0) return 0;
    int* a = new int[kCount]; 
    int n = 0; 
    collect(root, a, n);
    long long s = 0; 
    for(int i = 0; i < n; i++) {
        s += a[i];
    } 
    delete[] a; 
    return s;
}

int TwoThreeTree::height() const { return heightNode(root); }

bool TwoThreeTree::nth(int n, int& result) const {
    int kCount = keyCount();
    if(n < 1 || n > kCount) return false;
    int* a = new int[kCount];
    int count = 0; 
    collect(root, a, count);
    result = a[n - 1];
    delete[] a; 
    return true;
}

void TwoThreeTree::printLevels() const { printLevelsNode(root); }
void TwoThreeTree::clear() { destroyNode(root); root = nullptr; }
void TwoThreeTree::exportKeys(int* output, int& count) const { count = 0; collect(root, output, count); }