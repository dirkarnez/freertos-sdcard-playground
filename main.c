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
