#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

int main(int argc, char* argv[]) {

    PlayerData* player_data = (struct player_data*)malloc(sizeof(PlayerData));

    //PlayerData* test_data = (struct player_data*)malloc(sizeof(PlayerData));

    Soldier* soldier_roster = (Soldier*)malloc(ROSTER_LENGTH * sizeof(Soldier));

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
        printf("%s\n", player_data->rank);
        printf("Level %d\n", player_data->level);
    }

    return 0;
}

