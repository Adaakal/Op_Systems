/** This algorithm is the Shortest-job-first (SJF) algorithm, which schedules tasks in order of the length of the tasks' next CPU burst. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sjf.h"


// Function to add tasks to the list
void addTask(Node** head, Task newTask) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error allocating memory for new Node.\n");
        exit(EXIT_FAILURE);
    }
    newNode->task = newTask;
    newNode->next = *head;
    *head = newNode;
}

// Reading tasks from a file
void readTasks(const char* filename, Node** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file.");
        exit(EXIT_FAILURE);
    }

    Task task;
    while (fscanf(file, "%[^,], %d, %d\n", task.name, &task.priority, &task.burst) == 3) {
        addTask(head, task);
    }
    fclose(file);

}


// Merge Sort the list based on CPU burst time
void mergeSort(Node** headRef) {
    Node* head = *headRef;
    Node* a;
    Node* b;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    split(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = sortedMerge(a, b);
}

Node* sortedMerge(Node* a, Node* b) {
    Node* result = NULL;

    if (a == NULL) {
        return b;
    } else if (b == NULL) {
        return a;
    }

    if (a->task.burst <= b->task.burst) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

// Execute tasks
void executeTasks(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("Process Name: %s\nPriority: %d\nBurst: %d\nTime in Processor: %d\n\n",
               current->task.name, current->task.priority, current->task.burst, current->task.burst);
        current = current->next;
    }
}

void freeList(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void split(Node* source, Node** frontRef, Node** backRef) {
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if(fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

