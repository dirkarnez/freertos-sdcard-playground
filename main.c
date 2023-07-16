/*
In this example, two tasks are created using the xTaskCreate function. 
Each task reads a different file using the read_file function, which is similar to the function in the previous example.

Note that each task has its own stack (4096 bytes in this case), 
which allows them to run concurrently without interfering with each other. 
The 5 argument specifies the priority of the task; tasks with higher priority will be scheduled first.

Another approach is to use non-blocking I/O functions and event loops 
to perform file I/O operations concurrently. This approach can be more memory-efficient, 
but it requires more advanced programming skills. ESP-IDF provides APIs 
for non-blocking I/O and event loops, including the esp_event_loop_create and esp_vfs_register functions.

Overall, concurrent file I/O in ESP chips requires careful consideration of 
memory and processing constraints, as well as a good 
understanding of the available APIs and programming strategies.
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

#define FILE1 "/sdcard/file1.txt"
#define FILE2 "/sdcard/file2.txt"

void read_file(void *filename) {
    FILE* f = fopen((const char*)filename, "r");
    if (f == NULL) {
        printf("Failed to open %s for reading\n", (const char*)filename);
        return;
    }

    char buf[1024];
    while (fgets(buf, sizeof(buf), f) != NULL) {
        printf("%s", buf);
    }

    fclose(f);
}

void app_main() {
    xTaskCreate(read_file, "file1_task", 4096, (void *)FILE1, 5, NULL);
    xTaskCreate(read_file, "file2_task", 4096, (void *)FILE2, 5, NULL);
}
