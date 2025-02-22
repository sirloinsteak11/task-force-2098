#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

int create_save_data(Soldier* soldier_array, PlayerData* player_data) {
    FILE* savefile = fopen(DEFAULT_SAVE, "wb");

    player_data ->rank = (char*)malloc(MAX_NAME_SIZE * sizeof(char));
    player_data->team_name = (char*)malloc(MAX_NAME_SIZE * sizeof(char));
    player_data->cmdr_name = (char*)malloc(MAX_NAME_SIZE * sizeof(char));

    char* team_name_input = (char*)malloc(MAX_NAME_SIZE * sizeof(char));
    init_roster(soldier_array);
    printf("Enter Team Name...\n");
    //scanf("%s", team_name_input);
    strcpy(team_name_input, "Rogue Phoenix");

    printf("%s\n", team_name_input);
    
    player_data->team_name = alloc_string(team_name_input);
    
    free(team_name_input);
    team_name_input = NULL;

    char* cmdr_name_input = (char*)malloc(MAX_NAME_SIZE * sizeof(char));
    printf("Enter Commander Name... ");
    strcpy(cmdr_name_input, "ZERO");
    printf("%s\n", cmdr_name_input);

    player_data->cmdr_name = alloc_string(cmdr_name_input);
    free(cmdr_name_input);
    cmdr_name_input = NULL;


    player_data->soldier_roster = soldier_array;
    player_data->exp = 0;
    player_data->level = 0;
    player_data->rank = "LT CMDR";
    player_data->name_length = strlen(player_data->team_name);
    player_data->rank_length = strlen(player_data->rank);
    player_data->cmdr_length = strlen(player_data->cmdr_name);

    if (savefile != NULL) {
        fwrite(&player_data->name_length, sizeof(int), 1, savefile);
        fwrite(&player_data->rank_length, sizeof(int), 1, savefile);
        fwrite(&player_data->cmdr_length, sizeof(int), 1, savefile);

        fwrite(player_data->team_name, sizeof(char), player_data->name_length + 1, savefile);
        fwrite(player_data->rank, sizeof(char), player_data->rank_length + 1, savefile);
        fwrite(&player_data->level, sizeof(int), 1, savefile);
        fwrite(&player_data->exp, sizeof(int), 1, savefile);
        fwrite(player_data->soldier_roster, sizeof(Soldier), ROSTER_LENGTH, savefile);
        fwrite(player_data->cmdr_name, sizeof(char), player_data->cmdr_length + 1, savefile);
        
        fclose(savefile);
        return 1;
    } else {
        fclose(savefile);
        return 0;
    }

}

int load_save_data(char* filename, PlayerData* player_data) {
    FILE* savefile = fopen(filename, "rb");

    if (savefile != NULL) {
        fread(&player_data->name_length, sizeof(int), 1, savefile);
        fread(&player_data->rank_length, sizeof(int), 1, savefile);
        fread(&player_data->cmdr_length, sizeof(int), 1, savefile);

        player_data->team_name = (char*)malloc(player_data->name_length+1 * sizeof(char));
        player_data->rank = (char*)malloc(player_data->rank_length+1 * sizeof(char));
        player_data->cmdr_name = (char*)malloc(player_data->cmdr_length+1 * sizeof(char));

        fread(player_data->team_name, sizeof(char), player_data->name_length + 1, savefile);
        fread(player_data->rank, sizeof(char), player_data->rank_length + 1, savefile);
        fread(&player_data->level, sizeof(int), 1, savefile);
        fread(&player_data->exp, sizeof(int), 1, savefile);

        player_data->soldier_roster = (Soldier*)malloc(ROSTER_LENGTH * sizeof(Soldier));
        fread(player_data->soldier_roster, sizeof(Soldier), ROSTER_LENGTH, savefile);

        fread(player_data->cmdr_name, sizeof(char), player_data->cmdr_length + 1, savefile);

        fclose(savefile);
        return 1;
    } else {
        fclose(savefile);
        return 0;
    }
}

int save_data(PlayerData* player_data) {
    FILE* savefile = fopen(DEFAULT_SAVE, "wb");

    if (savefile != NULL) {
        fwrite(&player_data->name_length, sizeof(int), 1, savefile);
        fwrite(&player_data->rank_length, sizeof(int), 1, savefile);
        fwrite(player_data->team_name, sizeof(char), strlen(player_data->team_name) + 1, savefile);
        fwrite(player_data->rank, sizeof(char), strlen(player_data->rank) + 1, savefile);
        fwrite(&player_data->level, sizeof(int), 1, savefile);
        fwrite(&player_data->exp, sizeof(int), 1, savefile);
        fwrite(player_data->soldier_roster, sizeof(Soldier), ROSTER_LENGTH, savefile);
        
        fclose(savefile);
        return 1;
    } else {
        fclose(savefile);
        return 0;
    }
}

void init_roster(Soldier* roster_array) {

    SoldierNode* soldier_roster_list = (SoldierNode*)malloc(sizeof(SoldierNode));
    soldier_roster_list = create_soldier_list(soldier_roster_list);

    //printing linked_list
    SoldierNode* list_ptr = soldier_roster_list;
    printf("Soldier Roster:\n");
    for (int i = 0; i < ROSTER_LENGTH; ++i) {
        printf("%s | %d | %s\n", list_ptr->soldier->name, list_ptr->soldier->rating, list_ptr->soldier->home_world);
        list_ptr = list_ptr->next;
    }

    list_ptr = soldier_roster_list;
    for (int i = 0; i < ROSTER_LENGTH; i++) {
        roster_array[i] = *list_ptr->soldier;
        list_ptr = list_ptr->next;
    }

    free(soldier_roster_list);
    soldier_roster_list = NULL;
    list_ptr = NULL;

    //priinting array
    printf("Soldier Roster Array:\n");
    for (int i = 0; i < ROSTER_LENGTH; i++) {
        printf("%s | %d | %s\n", roster_array[i].name, roster_array[i].rating, roster_array[i].home_world);
    }
}

SoldierNode* create_soldier_list(SoldierNode* soldier_head) {
    
    soldier_head = (SoldierNode*)malloc(sizeof(SoldierNode));
    SoldierNode* ptr = soldier_head;

    for (int i = 0; i < ROSTER_LENGTH; i++) {
        ptr->next = (SoldierNode*)malloc(sizeof(SoldierNode));
        ptr->soldier = create_soldier(ptr->soldier);
        ptr = ptr->next;
    }
    ptr->next = NULL;

    return soldier_head;
}

Soldier* create_soldier(Soldier* soldier) {
    soldier = (Soldier*)malloc(sizeof(Soldier));

    soldier->name = (char*)malloc(MAX_NAME_SIZE * sizeof(char));
    soldier->name = strcpy(soldier->name, "placeholder_name");
    soldier->rating = 99;
    soldier->home_world = (char*)malloc(MAX_NAME_SIZE * sizeof(char));
    soldier->home_world = strcpy(soldier->home_world, "placeholder_homeworld");

    return soldier;
}