#ifndef PRIORITY_H
#define PRIORITY_H

typedef struct
{
    char name[10];
    int priority;
    int burst;
} Task;

typedef struct node
{
    Task task;
    struct node *next;
} Node;

void readTasks(const char *filename);
void executeTasksBasedOnPriority();
void freeMemory();

#endif