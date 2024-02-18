// Header file that defines the Task and Node structures and declares all functions used in priority_rr.c.

#ifndef PRIORITY_RR_H
#define PRIORITY_RR_H

#define MAX_PRIORITY 10

typedef struct
{
    char name[10];
    int priority;
    int burst;          // Original burst time
    int remainingBurst; // Remaining burst time to track during execution
} Task;

typedef struct node
{
    Task task;
    struct node *next;
} Node;

void initializePriorityQueues(void);
void addTask(int priority, Task task);
void executeTaskRoundRobin(Node **queue);
void readTasks(const char *filename);
void scheduleTasks();
void freeMemory();

#endif