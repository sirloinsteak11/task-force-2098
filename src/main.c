#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

PlayerData* player_data;

//PlayerData* test_data = (struct player_data*)malloc(sizeof(PlayerData));

Soldier** soldier_roster;

void free_memory() {
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

int main(int argc, char* argv[]) {

    player_data = (struct player_data*)malloc(sizeof(PlayerData));

    //PlayerData* test_data = (struct player_data*)malloc(sizeof(PlayerData));

    soldier_roster = (Soldier**)malloc(ROSTER_LENGTH * sizeof(Soldier*));

    if (argc <= 1) {
        int save_success = create_save_data(soldier_roster, player_data);

        if (!save_success) {
            printf("unable to create save data :(\n");
            return 1;
        }
    }

    if (argc > 1) {
        int load_success = load_save_data(argv[1], player_data);

        if (!load_success) {
            printf("unable to load savedata\n");
            return 1;
        }

        printf("Loaded Data\n");
        printf("-----------\n");
        printf("%s\n", player_data->team_name);
        printf("%s %s\n", player_data->rank, player_data->cmdr_name);
        printf("Level %d\n", player_data->level);
    }

    intro_text();
    write_text("For a complete list of commands, type \"help\"\n", 45, 0);
    main_loop(player_data);

    free_memory();

    return 0;
}