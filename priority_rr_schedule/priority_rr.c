#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_rr.h"

Node *priorityQueues[MAX_PRIORITY];

void initializePriorityQueues()
{
    for (int i = 0; i < MAX_PRIORITY; i++)
    {
        priorityQueues[i] = NULL;
    }
}

void addTask(int priority, Task newTask)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        fprintf(stderr, "Failed to allocate memory for a new task.\n");
        exit(EXIT_FAILURE);
    }
    newNode->task = newTask;
    newNode->next = priorityQueues[priority - 1]; // Priority 1-10 maps to index 0-9
    priorityQueues[priority - 1] = newNode;
}

#define TIME_QUANTUM 10
void executeTaskRoundRobin(Node **queue)
{
    Node *current = *queue, *prev = NULL;
    Node *last = *queue;
    // Find the initial last node
    while (last && last->next)
    {
        last = last->next;
    }

    while (current != NULL)
    {
        // Execute the current task
        int timeSlice = (current->task.remainingBurst > TIME_QUANTUM) ? TIME_QUANTUM : current->task.remainingBurst;
        printf("Executing Task: %s, Priority: %d, Burst Used: %d\n",
               current->task.name, current->task.priority, timeSlice);
        current->task.remainingBurst -= timeSlice;

        if (current->task.remainingBurst > 0)
        {
            // If task is not completed and not the last node, requeue it
            if (current != last)
            {
                // Remove current task from its position
                if (prev)
                    prev->next = current->next;
                else
                    *queue = current->next; // Update head if needed

                // Append current task at the end
                last->next = current;
                current->next = NULL;
                last = current; // Update last to the new last node

                // Prepare for next iteration
                current = (prev) ? prev->next : *queue;
            }
            else
            {
                // If current is the last node, just update pointers for the next iteration
                prev = current;
                current = current->next;
            }
        }
        else
        {
            // Task completed, remove it from the queue
            printf("Task %s completed.\n", current->task.name);
            Node *temp = current;
            current = current->next; // Move to next task before freeing

            if (prev)
                prev->next = current; // Bypass completed task
            else
                *queue = current; // Update head if the completed task was first

            free(temp); // Free the memory of the completed task
        }
    }
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
        addTask(task.priority, task);
    }
    fclose(file);
}

void scheduleTasks()
{
    for (int i = MAX_PRIORITY; i >= 0; i--)
    {
        if (priorityQueues[i] != NULL)
        {
            executeTaskRoundRobin(&priorityQueues[i]);
        }
    }
}

void freeMemory()
{
    for (int i = 0; i < MAX_PRIORITY; i++)
    {
        Node *current = priorityQueues[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// void executeTaskRoundRobin(Node **queue)
// {
//     Node *prev = NULL, *current = *queue, *last = NULL;

//     // First, find the last node in the queue to know where to append tasks that need requeueing
//     if (current != NULL)
//     {
//         for (last = current; last->next != NULL; last = last->next)
//             ;
//     }

//     while (current != NULL)
//     {
//         int timeSlice = (current->task.remainingBurst > TIME_QUANTUM) ? TIME_QUANTUM : current->task.remainingBurst;
//         printf("Executing Task: %s, Priority: %d, Burst Used: %d\n",
//                current->task.name, current->task.priority, timeSlice);

//         current->task.remainingBurst -= timeSlice;

//         if (current->task.remainingBurst <= 0)
//         {
//             printf("Task %s completed.\n", current->task.name);
//             // Remove the completed task from the queue
//             if (prev != NULL)
//             {
//                 prev->next = current->next; // Link the previous node to the next, bypassing current
//             }
//             else
//             {
//                 *queue = current->next; // Update the head of the queue if the completed task was the first
//             }

//             Node *completedTask = current;
//             current = current->next; // Move to the next task before freeing memory
//             free(completedTask);     // Free the memory of the completed task

//             if (prev == NULL)
//             {
//                 // If we removed the head, last might need updating if it pointed to the removed node
//                 last = (last == completedTask) ? *queue : last;
//             }
//         }
//         else
//         {
//             // For tasks that need more time and are not already the last node
//             if (current->next != NULL)
//             {
//                 Node *taskToMove = current;
//                 current = current->next; // Move to the next task before requeueing

//                 if (prev != NULL)
//                     prev->next = current; // Unlink taskToMove from its current position
//                 else
//                     *queue = current; // Update the head if necessary

//                 last->next = taskToMove; // Append it at the end
//                 taskToMove->next = NULL; // Now it's the last node
//                 last = taskToMove;       // Update the last pointer

//                 continue; // Skip the prev update at the end of the loop
//             }
//             else
//             {
//                 current = current->next; // Move to the next task
//             }
//         }

//         // Only update prev if we didn't remove the current node from the queue
//         if (prev == NULL || current != prev->next)
//         {
//             prev = (prev == NULL) ? *queue : prev->next;
//         }
//     }
// }
