#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>
#include <string>
#include <utility> 
using namespace std;
using namespace std::chrono;

// 1. Сортування підрахунком
void countingSort(vector<int>& arr, long long& comparisons, long long& swaps) {
    if (arr.empty())
        return;

    int max_val = arr[0];
    int min_val = arr[0];

    for (size_t i = 1; i < arr.size(); i++) {
        comparisons += 2;
        if (arr[i] > max_val)
            max_val = arr[i];
        else if (arr[i] < min_val) 
            min_val = arr[i];
    }

    int range = max_val - min_val + 1;
    vector<int> count(range, 0);
    vector<int> output(arr.size());

    for (size_t i = 0; i < arr.size(); i++) {
        count[arr[i] - min_val]++;
    }

    for (size_t i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    for (int i = static_cast<int>(arr.size()) - 1; i >= 0; i--) {
        output[count[arr[i] - min_val] - 1] = arr[i];
        count[arr[i] - min_val]--;
        swaps++;
    }

    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
        swaps++;
    }
}

// 2. Гномове сортування
void gnomeSort(vector<int>& arr, long long& comparisons, long long& swaps) {
    int index = 0;
    int n = static_cast<int>(arr.size());

    while (index < n) {
        if (index == 0) {
            index++;
        }

        comparisons++;
        if (arr[index] >= arr[index - 1]) {
            index++;
        }
        else {
            swap(arr[index], arr[index - 1]);
            swaps++;
            index--;
        }
    }
}

// 3. Сортування Шелла 
void shellSort(vector<int>& arr, long long& comparisons, long long& swaps) {
    int n = static_cast<int>(arr.size());

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;

            for (j = i; j >= gap; j -= gap) {
                comparisons++;
                if (arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    swaps++;
                }
                else {
                    break;
                }
            }
            arr[j] = temp;
            swaps++;
        }
    }
}

// Генерація масивів
vector<int> generateArray(int size, const string& type) {
    vector<int> arr(size);
   /* random_device використовується для отримання початкового значення 
   mt19937 — генератор псевдовипадкових чисел
   uniform_int_distribution задає діапазон випадкових значень*/
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 99999);

    if (type == "Random") {
        for (int i = 0; i < size; i++) arr[i] = dis(gen);
    }
    else if (type == "Sorted") {
        for (int i = 0; i < size; i++) arr[i] = i * 10;
    }
    else if (type == "Reverse") {
        for (int i = 0; i < size; i++) arr[i] = (size - i) * 10;
    }
    return arr;
}

// Запуск тесту
void runTest(const string& algoName, void (*sortFunc)(vector<int>&, long long&, long long&), int size, const string& type) {
    vector<int> arr = generateArray(size, type);

    long long comparisons = 0;
    long long swaps = 0;

    auto start = high_resolution_clock::now();

    sortFunc(arr, comparisons, swaps);

    auto stop = high_resolution_clock::now();
    double duration_ms = duration<double, milli>(stop - start).count();

    cout << left << setw(15) << algoName << setw(10) << size << setw(12) << type << setw(15) 
    << duration_ms << setw(15) << comparisons << setw(15) << swaps << endl;
}

int main() {
    vector<int> sizes = { 100, 1000, 10000 };
    vector<string> types = { "Random", "Sorted", "Reverse" };
cout << "==================================================================================\n";
    cout << left << setw(15) << "Algorithm"
        << setw(10) << "Size"
        << setw(12) << "State"
        << setw(15) << "Time(ms)"
        << setw(15) << "Comparisons"
        << setw(15) << "Swaps/Moves" << endl;
    cout << "==================================================================================\n";

    for (int size : sizes) {
        for (const string& type : types) {
            runTest("Counting", countingSort, size, type);
            runTest("Gnome", gnomeSort, size, type);
            runTest("Shell", shellSort, size, type);
            cout << "----------------------------------------------------------------------------------\n";
        }
    }

    return 0;
}

