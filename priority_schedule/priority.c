#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority.h"

Node *tasks = NULL;

void addTask(Task newTask)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node **current = &tasks;

    if (!newNode)
    {
        fprintf(stderr, "Failed to allocate memory for a new task.\n");
        exit(EXIT_FAILURE);
    }
    newNode->task = newTask;

    // Insert in sorted order (higher priority first)
    while (*current != NULL && (*current)->task.priority > newTask.priority)
    {
        current = &(*current)->next;
    }
    newNode->next = *current;
    *current = newNode;
}

void readTasks(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("failed to open the input file");
        exit(EXIT_FAILURE);
    }

    Task task;
    while (fscanf(file, "%[^,], %d, %d\n", task.name, &task.priority, &task.burst) == 3)
    {
        addTask(task);
    }
    fclose(file);
}

void executeTasksBasedOnPriority()
{
    Node *current = tasks;
    while (current != NULL)
    {
        printf("Process Name: %s\nPriority: %d\nBurst: %d\nTime in Processor: %d\n\n",
               current->task.name, current->task.priority, current->task.burst, current->task.burst);
        current = current->next;
    }
}

void freeMemory()
{
    Node *current = tasks;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}
