#include <stdlib.h>
#include "game.h"

static PlayerData* player_data = NULL;
static Soldier** soldier_roster = NULL;

void datainit() {
    player_data = (PlayerData*)malloc(sizeof(PlayerData));
    //PlayerData* test_data = (struct player_data*)malloc(sizeof(PlayerData));
    player_data->soldier_roster = (Soldier**)malloc(ROSTER_LENGTH * sizeof(Soldier*));
    soldier_roster = player_data->soldier_roster;
}

void set_player_data(PlayerData* data) {
    player_data = data;
}

PlayerData* get_player_data() {
    return player_data;
}

void set_soldier_roster(Soldier** roster) {
    soldier_roster = roster;
}

Soldier** get_soldier_roster() {
    return soldier_roster;
}