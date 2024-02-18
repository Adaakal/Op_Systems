#include <stdio.h>
#include <stdlib.h>
#include "sjf.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <schedule_file>\n", argv[0]);
        return 1;
    }

    Node *head = NULL;
    readTasks(argv[1], &head);
    mergeSort(&head);
    executeTasks(head);
    freeList(head);

    return 0;
}
