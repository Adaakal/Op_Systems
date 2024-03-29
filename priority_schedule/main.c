#include "priority.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <tasks_file>\n", argv[0]);
        return 1;
    }

    readTasks(argv[1]);
    executeTasksBasedOnPriority();
    freeMemory();

    return 0;
}