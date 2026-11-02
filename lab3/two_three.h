#ifndef TWO_THREE_H
#define TWO_THREE_H
#include <iostream>

struct TwoThreeNode {
    int keys[2];
    int count;
    TwoThreeNode* child[3];
    TwoThreeNode() : keys{0,0}, count(0), child{nullptr,nullptr,nullptr} {}
    bool leaf() const { return child[0] == nullptr; }
};

class TwoThreeTree {
    TwoThreeNode* root;
    struct Promotion { bool split; int key; TwoThreeNode* right; };
    static Promotion insertRec(TwoThreeNode* n, int key);
    static bool containsNode(TwoThreeNode* n, int key);
    static void collect(TwoThreeNode* n, int* a, int& i);
    static int countKeysNode(TwoThreeNode* n);
    static void destroyNode(TwoThreeNode* n);
    static int heightNode(TwoThreeNode* n);
    static void printLevelsNode(TwoThreeNode* root);
public:
    TwoThreeTree() : root(nullptr) {}
    ~TwoThreeTree() { clear(); }
    bool insert(int key);
    bool contains(int key) const;
    bool erase(int key);
    long long sum() const;
    int height() const;
    int keyCount() const;
    bool nth(int n, int& result) const;
    void printLevels() const;
    void clear();
    void exportKeys(int* output, int& count) const;
};
#endif
