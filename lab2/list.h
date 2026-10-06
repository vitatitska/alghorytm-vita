#include "list.h"

void addHead(Node*& head, Node*& tail, int value)
{
    Node* p = new Node;

    p->data = value;
    p->next = head;

    head = p;

    if (tail == nullptr)
        tail = p;
}

void addTail(Node*& head, Node*& tail, int value)
{
    Node* p = new Node;

    p->data = value;
    p->next = nullptr;

    if (head == nullptr)
    {
        head = p;
        tail = p;
    }
    else
    {
        tail->next = p;
        tail = p;
    }
}

bool isEmpty(Node* head)
{
    return head == nullptr;
}

void printList(Node* head)
{
    Node* p = head;

    while (p != nullptr)
    {
        // Виведення числа відбувається в source.cpp
        p = p->next;
    }
}

int getLength(Node* head)
{
    int length = 0;
    Node* p = head;

    while (p != nullptr)
    {
        length++;
        p = p->next;
    }

    return length;
}

void deleteFirst(Node*& head, Node*& tail)
{
    if (head == nullptr)
        return;

    Node* p = head;

    head = head->next;

    delete p;

    if (head == nullptr)
        tail = nullptr;
}

void printPositiveReverse(Node* head)
{
    if (head == nullptr)
        return;

    printPositiveReverse(head->next);

    if (head->data > 0)
    {
        // Виведення числа відбувається в source.cpp
    }
}

bool hasCycle(Node* head)
{
    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}

void freeList(Node*& head, Node*& tail)
{
    Node* p;

    while (head != nullptr)
    {
        p = head;
        head = head->next;
        delete p;
    }

    tail = nullptr;
}
