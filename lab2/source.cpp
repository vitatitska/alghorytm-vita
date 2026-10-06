#include "list.h"
#include <unistd.h>

void printNumber(int x)
{
    char s[20];
    int i = 0;

    if (x == 0)
    {
        write(1, "0", 1);
        return;
    }

    if (x < 0)
    {
        write(1, "-", 1);
        x = -x;
    }

    while (x > 0)
    {
        s[i++] = '0' + x % 10;
        x /= 10;
    }

    while (i > 0)
    {
        i--;
        write(1, &s[i], 1);
    }
}

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
        printNumber(p->data);
        write(1, " ", 1);

        p = p->next;
    }

    write(1, "\n", 1);
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
        printNumber(head->data);
        write(1, " ", 1);
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
    while (head != nullptr)
    {
        Node* p = head;
        head = head->next;
        delete p;
    }

    tail = nullptr;
}
