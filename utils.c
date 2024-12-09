// utils.c
#include "utils.h"
#include <stdio.h>

void load_maze_from_file(int maze[28][31], const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open maze file: %s\n", filename);
        return;
    }

    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 31; j++) {
            if (fscanf(file, "%d", &maze[i][j]) != 1) {
                fprintf(stderr, "Error reading maze data from file: %s\n", filename);
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
}
