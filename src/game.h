/*

    game - handles all gameplay and events code

*/


#ifndef GAME_H
#define GAME_H

#include "items.h"
#include "data.h"
#include "helper.h"

#define ROSTER_LENGTH 6
#define MAX_NAME_SIZE 50
#define DEFAULT_SAVE "savefile"

typedef struct {

    char* location;
    int value;
    int recommended_level;
    int recommended_team_rating;

} Contract;

void main_loop();
int process_input(char *input);
void intro_text();
void file_to_text(char *filename);
void write_text(char *text, int len, int cinematic);

#endif