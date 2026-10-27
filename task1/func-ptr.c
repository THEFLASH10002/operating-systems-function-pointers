#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "process.h" /* Process and the number of input records, P_SIZE */
#include "util.h"

#define DEBUG 0

typedef int (*Comparer)(const void *a, const void *b);

/* qsort comparator: larger numeric priority comes first.
   For equal priorities, an earlier arrival time comes first.
   Returning negative/positive tells qsort which record comes first. */
int my_comparer(const void *this, const void *that)
{
    const Process *a = (const Process *)this;
    const Process *b = (const Process *)that;

    if (a->priority > b->priority) return -1;
    if (a->priority < b->priority) return 1;
    if (a->arrival_time < b->arrival_time) return -1;
    if (a->arrival_time > b->arrival_time) return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./func-ptr <input-file-path>\n");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: Invalid filepath\n");
        return 1;
    }

    Process *processes = parse_file(input_file);
    Comparer process_comparer = &my_comparer;
#if DEBUG
    for (int i = 0; i < P_SIZE; i++) {
        printf("%d (%d, %d) ", processes[i].pid,
               processes[i].priority, processes[i].arrival_time);
    }
    printf("\n");
#endif
    qsort(processes, P_SIZE, sizeof(Process), process_comparer);
    for (int i = 0; i < P_SIZE; i++) {
        printf("%d (%d, %d)\n", processes[i].pid,
               processes[i].priority, processes[i].arrival_time);
    }
    free(processes);
    fclose(input_file);
    return 0;
}
