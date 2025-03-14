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
#define LONG_PAUSE 750 * 100

int in_prompt() {
    PlayerData* player_data = get_player_data();
    printf("%s %s $> ", player_data->rank, player_data->cmdr_name);
    return 1;
}



void main_loop() {
    PlayerData* player_data = get_player_data();
    char input_buffer[256];

    while (in_prompt() && fgets(input_buffer, 256, stdin) != NULL) {
        if (process_input(input_buffer) == 1) {
            save_data(player_data);
            break;
        }
        memset(input_buffer, 0, sizeof(input_buffer));
    }

    /*
    for (;;) {
        
        //write_text(input_buffer, strlen(input_buffer), 0);
        if (process_input(input_buffer) == 1) {
            save_data(player_data);
            break;
        }
    }*/
}

int process_input(char* input) {
    if (strcmp(input, "help\n") == 0) {
        file_to_text("help.txt");
    }
    if (strcmp(input, "exit\n") == 0) {
        write_text("saving and exiting...", 22, 1);
        write_text("goodbye", 8, 1);
        return 1;
    }
    if (strcmp(input, "profile\n") == 0) {
        print_profile();
    }
    if (strcmp(input, "roster\n") == 0) {
        print_roster();
    }
    return 0;
}

void print_profile() {
    PlayerData* player_data = get_player_data();
    //Soldier** soldier_array = soldier_array;

    write_text("-----------", 12, 0);
    write_text(player_data->team_name, player_data->name_length, 0);
    printf("%s %s\n", player_data->rank, player_data->cmdr_name);
    printf("Level %d\n", player_data->level);
    printf("-----------\n");
    print_roster();
}

void print_roster() {
    Soldier** soldier_roster = get_soldier_roster();
    
    for (int i = 0; i < ROSTER_LENGTH; i++) {
        printf("%s | %d | %s\n", soldier_roster[i]->name, soldier_roster[i]->rating, soldier_roster[i]->home_world);
    }
}

void free_all_memory() {
    PlayerData* player_data = get_player_data();
    Soldier** soldier_roster = get_soldier_roster();
    /*
    for (int i = 0; i < MAX_NAME_SIZE; i++) {
        free(player_data->cmdr_name[i]);
        free(player_data->team_name[i]);
        free(player_data->rank[i]);
    }*/

    free(player_data->cmdr_name);
    free(player_data->team_name);
    free(player_data->rank);
    free(player_data);

    /*
    for (int i = 0; i < player_data->cmdr_length; ++i) {
        free(player_data->cmdr_name[i]);
    }
    for (int i = 0; i < player_data->name_length; ++i) {
        free(player_data->team_name[i]);
    }
    for (int i = 0; i < player_data->rank_length; ++i) {
        free(player_data->rank[i]);
    }*/

    for (int i = 0; i < ROSTER_LENGTH; i++) {
        free(soldier_roster[i]->name);
        free(soldier_roster[i]->home_world);
        free(soldier_roster[i]);
    }
    free(soldier_roster);
}

void intro_text() {
    char skip_intro_input[256];
    write_text("Do you wish to skip the intro? (y/n)", 37, 0);
    if (fgets(skip_intro_input, 256, stdin) == NULL) {
        perror("fgets");
        printf("error occurred... skipping intro\n");
        return;
    }

    if (strcmp(skip_intro_input, "y\n") == 0) {
        return;
    }

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
    char* filepath = (char*)malloc(sizeof(char) * 256);
    strcpy(filepath, "src/textfiles/");
    strcat(filepath, filename);
    FILE * file = fopen(filepath, "r");
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

        write_text(line, read, 0);
    }

    fclose(file);
    if (line)
        free(line);

    free(filepath);
}

void write_text(char* text, int len, int cinematic) {
    int factor = 2;
    int long_pause = SHORT_PAUSE;
    if (cinematic) {
        long_pause = LONG_PAUSE;
        factor = 1;
    }

    for (int i = 0; i < len-1; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(SHORT_PAUSE / factor);
    }
    usleep (long_pause);
    printf("%c", text[len-1]);
    if (!cinematic) {
        printf("\n");
    }
}

