#include <stdio.h>
#include "priority_rr.h"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tasks_file>\n", argv[0]);
        return 1;
    }

    initializePriorityQueues();
    readTasks(argv[1]);
    scheduleTasks();
    freeMemory();

    return 0;
}

