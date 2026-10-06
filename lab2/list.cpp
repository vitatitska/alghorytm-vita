#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

// Додавання елемента на початок списку
void addHead(Node*& head, Node*& tail, int value)
{
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;

    head = newNode;

    if (tail == nullptr)
    {
        tail = newNode;
    }
}

// Додавання елемента в кінець списку
void addTail(Node*& head, Node*& tail, int value)
{
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

// Перевірка, чи список порожній
bool isEmpty(Node* head)
{
    return head == nullptr;
}

// Виведення списку
void printList(Node* head)
{
    if (isEmpty(head))
    {
        cout << "List is empty." << endl;
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

// Визначення довжини списку
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

// Видалення першого елемента
void deleteFirst(Node*& head, Node*& tail)
{
    if (isEmpty(head))
    {
        return;
    }

    Node* temp = head;
    head = head->next;

    delete temp;

    if (head == nullptr)
    {
        tail = nullptr;
    }
}

// Виведення додатних елементів у зворотному порядку
void printPositiveReverse(Node* head)
{
    if (head == nullptr)
    {
        return;
    }

    printPositiveReverse(head->next);

    if (head->data > 0)
    {
        cout << head->data << " ";
    }
}

// Перевірка на наявність циклу
bool hasCycle(Node* head)
{
    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            return true;
        }
    }

    return false;
}

// Звільнення пам'яті
void freeList(Node*& head, Node*& tail)
{
    Node* current = head;

    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
    tail = nullptr;
}
