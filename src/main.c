#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

// TODO: CREATE INTERFACE FOR GAME DATA BASED ON GETTER AND SETTER IN GAME.C PLACE IN SEPARATE FILE

int main(int argc, char* argv[]) {

    datainit();

    PlayerData* player_data = get_player_data();

    //PlayerData* test_data = (struct player_data*)malloc(sizeof(PlayerData));

    
    
    Soldier** soldier_roster = get_soldier_roster();

    if (argc <= 1) {
        int save_success = create_save_data(player_data);

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

        print_profile();
    }

    intro_text();
    write_text("For a complete list of commands, type \"help\"\n", 45, 0);

    main_loop();

    free_all_memory();

    return 0;
}