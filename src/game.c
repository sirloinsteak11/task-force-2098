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

void main_loop(PlayerData* player_data) {
    char input_buffer[256];

    for (;;) {
        printf("%s %s$> ", player_data->rank, player_data->cmdr_name);
        fgets(input_buffer, 256, stdin);
        //write_text(input_buffer, strlen(input_buffer), 0);
        if (process_input(input_buffer) == 1) {
            save_data(player_data);
            break;
        }
    }
}

int process_input(char* input) {
    if (strcmp(input, "help") == 0) {
        file_to_text("intro.txt");
    }
    if (strcmp(input, "exit") == 0) {
        write_text("saving and exiting...", 22, 1);
        return 1;
    }
    return 0;
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

void file_to_text(char* filename) {
    filename = strcat("src/textfiles/", filename);
    FILE * file = fopen(filename, "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if (file == NULL) {
        printf("introfile cannot be opened\n");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, file)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);

        write_text(line, read, 1);
    }

    fclose(file);
    if (line)
        free(line);
}

void write_text(char* text, int len, int cinematic) {
    int factor = 2;
    int long_pause = SHORT_PAUSE;
    if (cinematic) {
        long_pause = LONG_PAUSE;
        factor = 1;
    }

    for (int i = 0; i < len; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(SHORT_PAUSE / factor);
    }
    usleep (long_pause);
    printf("\n");
}

