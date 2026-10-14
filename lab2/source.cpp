#include <iostream>
#include "list.h"

using namespace std;

int main()
{
  Node* head = nullptr;
  int n = 0;

  cout << "Введіть кількість елементів: ";
  if (!(cin >> n) || n < 0)
  {
    cout << "Помилка: потрібно ввести невід'ємне ціле число." << endl;
    return 1;
  }

  cout << "Введіть " << n << " елементів:" << endl;
  for (int i = 0; i < n; i++)
  {
    cout << i + 1 << ") ";
    int value;
    if (!(cin >> value))
    {
      cout << "Помилка: потрібно ввести ціле число." << endl;
      clearList(head);
      return 1;
    }
    addTail(head, value);
  }

  cout << "\nПочатковий список: ";
  printList(head);
  cout << "Довжина: " << getLength(head) << endl;

  int movesA = 0, movesB = 0, movesC = 0;

  cout << "\n--- ЗАВДАННЯ А: видалити перший елемент ---" << endl;
  removeFirst(head, movesA);
  cout << "Список: ";
  printList(head);
  cout << "Довжина: " << getLength(head) << endl;

  cout << "\n--- ЗАВДАННЯ Б: додатні елементи в оберненому порядку ---" << endl;
  printPositiveReversed(head, movesB);
  cout << "Список: ";
  printList(head);
  cout << "Довжина: " << getLength(head) << endl;

  cout << "\n--- ЗАВДАННЯ В: перевірка наявності циклу ---" << endl;
  bool cycle = hasCycle(head, movesC);
  cout << (cycle ? "Цикл є." : "Циклу немає.") << endl;
  cout << "Список: ";
  printList(head);
  cout << "Довжина: " << getLength(head) << endl;

  // ----- Таблиця переходів за покажчиком -----
  cout << "\n==============================" << endl;
  cout << "Завдання\tПереходів" << endl;
  cout << "------------------------------" << endl;
  cout << "   А    \t   " << movesA << endl;
  cout << "   Б    \t   " << movesB << endl;
  cout << "   В    \t   " << movesC << endl;
  cout << "==============================" << endl;

  clearList(head);
  return 0;
}
