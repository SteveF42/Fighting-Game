/*
    Filename moves.h
    description: header file that declares the base class Move and all of its child classes 
*/
#ifndef MOVES_H
#define MOVES_H

#include<iostream>
#include<vector>
#include<string>
#include<random>
#include"../character.h"
typedef std::string string_std;
class Character;
/*
    Base Move for each character to be implemented in their own class
*/
class Move{
public:    
    virtual void display_stats();
    //sends out an attack message and updates players pp
    virtual void apply_attack_to_player(Character* player, Character* other);
    double calculate_total_damage(Character* player);
    double calculate_armor_damage(Character* other,double current_damage);
    int get_pp(){return this->PP_cost;}

protected:
    bool calculate_special_chance(double chance_num);
    int PP_cost;
    double damage;
    string_std name;
    string_std description;
    string_std display_message_on_attack;
};

/*
    Description: Base class which will hold onto all of the chosen Character moves
*/
class Character_moves{
public:

    Move* select_move();
    void choose_moves();
    //displays the moves that user has chosen
    void display_chosen_moves();
    //displays all move options available to the player
    void show_possible_moves();
    ~Character_moves();
protected:

    std::vector<Move*> player_moves;
    std::vector<Move*> all_choices;
};

class Wizard_moves : public Character_moves{
public:
    Wizard_moves();
private:

};

class Mage_moves : public Character_moves{
public:
    Mage_moves();
private:

};

#endif