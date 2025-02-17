#ifndef GEAR_H
#define GEAR_H

typedef struct {

    char* name;
    int sell_price;
    char* negative_effect;
    int negative_value;
    char* positive_effect;
    int positive_value;

} Armor;

typedef Armor Weapon;

typedef struct {

    char* name;
    int rating;
    char* home_world;
    Weapon weapon;
    Armor helmet;
    Armor armor;
    
} Soldier;

#endif