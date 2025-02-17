#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helper.h"

void print_array(Soldier* roster_array) {
    printf("Soldier Roster Array:\n");
    for (int i = 0; i < ROSTER_LENGTH; i++) {
        printf("%s | %d | %s\n", roster_array[i].name, roster_array[i].rating, roster_array[i].home_world);
    }
}

char* alloc_string(char* string) {

    int string_len = 0;
    for (int i = 0; string[i] != 0; i++) {
        string_len++;
    }

    char* dynam_string = (char*)malloc(string_len * sizeof(char));
    
    for (int i = 0; string[i] != 0; i++) {
        dynam_string[i] = string[i];
    }

    return dynam_string;
}