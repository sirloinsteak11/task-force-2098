#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

void main_loop() {
    for (;;) {
        
    }
}

void intro() {
    FILE * introfile = fopen("textfiles/intro.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if (introfile == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, introfile)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
    }

    fclose(introfile);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}

