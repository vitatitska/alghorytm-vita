#include "list.h"
#include <iostream>

using namespace std;

void addHead(Node*& head, int value)
{
  Node* newNode = new Node;
  newNode->data = value;
  newNode->next = head;
  head = newNode;
}

void addTail(Node*& head, int value)
{
  Node* newNode = new Node;
  newNode->data = value;
  newNode->next = nullptr;

  if (head == nullptr)
  {
    head = newNode;
    return;
  }

  Node* current = head;
  while (current->next != nullptr)
  {
    current = current->next;
  }
  current->next = newNode;
}

bool isEmpty(Node* head)
{
  return head == nullptr;
}

void printList(Node* head)
{
  if (isEmpty(head))
  {
    cout << "(список порожній)" << endl;
    return;
  }

  Node* current = head;
  while (current != nullptr)
  {
    cout << current->data << " ";
    current = current->next;
  }
  cout << endl;
}

void clearList(Node*& head)
{
  while (head != nullptr)
  {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
}

int getLength(Node* head)
{
  int length = 0;
  Node* current = head;
  while (current != nullptr)
  {
    length++;
    current = current->next;
  }
  return length;
}

// Видалити з непорожнього списку перший елемент(завдання А)
void removeFirst(Node*& head, int& moves)
{
  if (isEmpty(head))
  {
    cout << "Список порожній, видаляти нічого." << endl;
    return;
  }

  Node* temp = head;
  head = head->next;   
  moves++;
  delete temp;
}

// Рекурсія йде вперед до кінця списку, а додатні елементи виводяться на зворотному шляху, тобто в оберненому порядку(завдання Б)
static void printPositiveReversedRec(Node* node, int& moves)
{
  if (node == nullptr)
    return;

  moves++; 
  printPositiveReversedRec(node->next, moves);

  if (node->data > 0)
    cout << node->data << " ";
}

void printPositiveReversed(Node* head, int& moves)
{
  printPositiveReversedRec(head, moves);
  cout << endl;
}

// Два покажчики: slow робить 1 крок, fast - 2 кроки. Якщо цикл є, fast наздожене slow (завдання В)
bool hasCycle(Node* head, int& moves)
{
  Node* slow = head;
  Node* fast = head;

  while (fast != nullptr && fast->next != nullptr)
  {
    slow = slow->next;           
    fast = fast->next->next;     
    moves += 3;

    if (slow == fast)
      return true;
  }
  return false;
}