#pragma once

struct Node
{
  int data;
  Node* next;
};

void addHead(Node*& head, int value);
void addTail(Node*& head, int value);
bool isEmpty(Node* head);
void printList(Node* head);
void clearList(Node*& head);
int getLength(Node* head);

void removeFirst(Node*& head, int& moves);            // А
void printPositiveReversed(Node* head, int& moves);   // Б
bool hasCycle(Node* head, int& moves);                // В