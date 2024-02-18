// Header file that defines the Task and Node structures and declares all functions used in sjf.c.

#ifndef SJF_H
#define SJF_H

typedef struct{
    char name[10];
    int priority;
    int burst;
} Task;

typedef struct node{
    Task task;
    struct node *next;
} Node;

void addTask(Node** head, Task newTask);
void readTasks(const char* filename, Node** head);
void mergeSort(Node** headRef);
Node* sortedMerge(Node* a, Node* b);
void executeTasks(Node* head);
void freeList(Node* head);
void split(Node* source, Node** frontRef, Node** backRef);





#endif