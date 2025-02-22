/*

    data - handles all game data and save file systems and algorithms

*/



#ifndef DATA_H
#define DATA_H

#include "game.h"
#include "items.h"
#include "helper.h"

typedef struct player_data {

    char* cmdr_name;
    char* team_name;
    int level;
    char* rank;
    int exp;
    Soldier* soldier_roster;
    int name_length;
    int rank_length;
    int cmdr_length;

} PlayerData;

typedef struct soldier_node{
    Soldier* soldier;
    struct soldier_node* next;
} SoldierNode;

int create_save_data(Soldier* soldier_array, PlayerData* player_data);
int load_save_data(char* filename, PlayerData* player_data);
int save_data(PlayerData *player_data);
void init_roster(Soldier *roster_array);
SoldierNode* create_soldier_list(SoldierNode* soldier_head);
Soldier* create_soldier(Soldier* soldier);
void print_array(Soldier* roster_array);

#endif