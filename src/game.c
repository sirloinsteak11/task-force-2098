#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#define sleep(x) Sleep(x)
#else
#include <unistd.h>
#endif

#include "game.h"

#define SHORT_PAUSE 25 * 1000
#define LONG_PAUSE 750 * 1000

void main_loop() {
    for (;;) {
        printf("%s %s");
    }
}

void intro_text() {
    FILE * introfile = fopen("src/textfiles/intro.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if (introfile == NULL) {
        printf("introfile cannot be opened\n");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, introfile)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);

        write_text(line, read, 1);
    }

    fclose(introfile);
    if (line)
        free(line);
}

void write_text(char* text, int len, int cinematic) {
    int factor = 2;
    if (cinematic)
        factor = 1;

    for (int i = 0; i < len; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(SHORT_PAUSE / factor);
    }
    usleep (LONG_PAUSE);
    printf("\n");
}

