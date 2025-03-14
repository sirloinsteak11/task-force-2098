/*

    game - handles all gameplay and events code
    public interfaces

*/


#ifndef GAME_H
#define GAME_H

#define ROSTER_LENGTH 6
#define MAX_NAME_SIZE 256
#define DEFAULT_SAVE "savefile"

typedef struct {

    char* location;
    int value;
    int recommended_level;
    int recommended_team_rating;

} Contract;

typedef struct {

    char* name;
    int sell_price;
    char* negative_effect;
    int negative_value;
    char* positive_effect;
    int positive_value;

} Armor;

typedef Armor Weapon;

typedef struct soldier {

    char* name;
    int rating;
    char* home_world;
    Weapon weapon;
    Armor helmet;
    Armor armor;
    
} Soldier;

void game_init();
void intro_text();
void file_to_text(char *filename);
void write_text(char *text, int len, int cinematic);

//helpers
void print_array(Soldier* roster_array);
char* alloc_string(char* string);
//end helpers

//savedata
typedef struct player_data {

    char* cmdr_name;
    char* team_name;
    int level;
    char* rank;
    int exp;
    Soldier** soldier_roster;
    int name_length;
    int rank_length;
    int cmdr_length;

} PlayerData;

// most likely unneeded
typedef struct soldier_node{
    Soldier* soldier;
    struct soldier_node* next;
} SoldierNode;

// savedata unfctions
int create_save_data(PlayerData* player_data);
int load_save_data(char* filename, PlayerData* player_data);
int save_data(PlayerData *player_data);
void init_roster(Soldier **roster_array);
SoldierNode* create_soldier_list(SoldierNode* soldier_head);
Soldier* create_soldier(Soldier* soldier);
void print_array(Soldier* roster_array);
// end savedata

// data interface
void datainit();
void set_player_data(PlayerData* player_data);
PlayerData* get_player_data();
void set_soldier_roster(Soldier** soldier_roster);
Soldier** get_soldier_roster();
//end data interface

#endif