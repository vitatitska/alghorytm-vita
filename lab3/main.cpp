#include "avl.h"
#include "two_three.h"
#include "red_black.h"
#include <iostream>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#endif

int readInt(const char* prompt) {
    int x;
    while (true) {
        std::cout << prompt;
        if (std::cin >> x) {
            return x;
        }
        std::cout << "Введіть ціле число!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void printAllTrees(const AVLTree& avl1, const TwoThreeTree& tt1, const AVLTree& avl2, const TwoThreeTree& tt2) {
    std::cout << "\n=== AVL-дерево T1 ===\n"; 
    avl1.printLevels();
    std::cout << "\n=== 2-3-дерево T1 ===\n"; 
    tt1.printLevels();
    std::cout << "\n=== AVL-дерево T2 ===\n"; 
    avl2.printLevels();
    std::cout << "\n=== 2-3-дерево T2 ===\n"; 
    tt2.printLevels();
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n1 = readInt("Кількість ключів T1: ");
    if (n1 < 0 || n1 > 100000) { 
        std::cout << "Некоректна кількість.\n"; 
        return 1; 
    }
    AVLTree avl1; 
    TwoThreeTree tt1;
    std::cout << "Введіть ключі T1: ";
    for (int i = 0; i < n1; ++i) { 
        int x; 
        if (!(std::cin >> x)) return 1;        
        avl1.insert(x); 
        tt1.insert(x); 
    }

    int n2 = readInt("Кількість ключів T2: ");
    if (n2 < 0 || n2 > 100000) { 
        std::cout << "Некоректна кількість.\n"; 
        return 1; 
    }
    AVLTree avl2; 
    TwoThreeTree tt2;
    std::cout << "Введіть ключі T2: ";
    for (int i = 0; i < n2; ++i) { 
        int x; 
        if (!(std::cin >> x)) return 1; 
        avl2.insert(x);
        tt2.insert(x); 
    }
    
    int N = readInt("Введіть N для завдання В: ");

    std::cout << "\n================ ПОЧАТКОВІ ДЕРЕВА ================";
    printAllTrees(avl1, tt1, avl2, tt2);

    // --- ЗАВДАННЯ А ---
    std::cout << "\n================ ЗАВДАННЯ A ================\n";
    std::cout << "Сума ключів T1 (AVL): " << avl1.sum() << "\n";
    std::cout << "Сума ключів T1 (2-3): " << tt1.sum() << "\n";
    printAllTrees(avl1, tt1, avl2, tt2);

    // --- ЗАВДАННЯ Б ---
    std::cout << "\n================ ЗАВДАННЯ Б ================\n";
    int count2 = tt2.keyCount();
    if (count2 > 0) {
        int* keys2 = new int[count2];
        int exported = 0;
        tt2.exportKeys(keys2, exported);
        for (int i = 0; i < exported; ++i) {
            avl1.erase(keys2[i]);
            tt1.erase(keys2[i]);
        }
        delete[] keys2;
    }
    std::cout << "AVL T1 та 2-3 T1 після видалення ключів з T2:\n";
    printAllTrees(avl1, tt1, avl2, tt2);

    // --- ЗАВДАННЯ В ---
    std::cout << "\n================ ЗАВДАННЯ В ================\n";
    AVLTree avlCopy;
    TwoThreeTree ttCopy;
    int count1 = tt1.keyCount();
    if (count1 > 0) {
        int* keys1 = new int[count1];
        int exp1 = 0;
        tt1.exportKeys(keys1, exp1);
        for (int i = 0; i < exp1; ++i) {
            avlCopy.insert(keys1[i]);
            ttCopy.insert(keys1[i]);
        }
        delete[] keys1;
    }

    int result;
    if (avlCopy.nth(N, result)) {
        std::cout << "AVL: " << N << "-й за зростанням ключ = " << result << "\n";
        for (int i = 1; i < N; ++i) {
            int minVal;
            avlCopy.nth(1, minVal);
            avlCopy.erase(minVal);
        }
    } else {
        std::cout << "AVL: немає " << N << "-го ключа\n";
    }

    if (tt1.nth(N, result)) {
        std::cout << "2-3: " << N << "-й за зростанням ключ = " << result << "\n";
        for (int i = 1; i < N; ++i) {
            int minVal;
            ttCopy.nth(1, minVal);
            ttCopy.erase(minVal);
        }
    } else {
        std::cout << "2-3: немає " << N << "-го ключа\n";
    }

    printAllTrees(avl1, tt1, avl2, tt2);
    std::cout << "\n=== Копія AVL-дерева T1 (після видалення N-1 ключів) ===\n"; 
    avlCopy.printLevels();
    std::cout << "\n=== Копія 2-3-дерева T1 (після видалення N-1 ключів) ===\n"; 
    ttCopy.printLevels();

    // --- ЗАВДАННЯ Г ---
    std::cout << "\n================ ЗАВДАННЯ Г ================\n";
    std::cout << "--- 2-3-дерево T1 до перетворення ---\n";
    tt1.printLevels();

    RedBlackTree rb;
    int countT1 = tt1.keyCount();
    if (countT1 > 0) {
        int* keysT1 = new int[countT1];
        int exported = 0;
        tt1.exportKeys(keysT1, exported);
        for (int i = 0; i < exported; ++i) {
            rb.insert(keysT1[i]);
        }
        delete[] keysT1;
    }

    printAllTrees(avl1, tt1, avl2, tt2);
    std::cout << "\n--- Left-Leaning Red-Black tree (LLRB) після перетворення T1 ---\n";
    rb.printLevels();

    return 0;
}
