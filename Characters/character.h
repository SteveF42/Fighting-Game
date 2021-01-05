/*
    Filename character.h
    description: Character header file that declares Character and all of its children classes
*/
#ifndef CHARACTER_H
#define CHARACTER_H

#include<iostream>
#include<random>
#include<string>
#include<tuple>
#include<unordered_map>
#include<vector>
#include"./moves/moves.h"
class Character_moves;
typedef std::string string_std;

// base class Character which will have children classes
class Character{
public:
    void select_moves();
    void choose_computer_attacks();
    void make_computer_attack();
    
    void update_player_stats(double health_stat, double attack_stat, double shield_stat, float crit, double crit_multiplier);
    void display_player_stats();
    void attack(Character* other);
    bool calculate_crit_chance();

    void update_pp_on_turn(){PP_points += 2;}
    double get_base_attack() {return this->base_attack;}
    double get_base_shield(){return this->base_shield;}
    double get_crit_multiplier(){return this->crit_multiplier;}
    double get_armor_hit_percent(){return armor_hit_percent;}
    int get_pp(){return this->PP_points;}
    void update_pp(int pp){this->PP_points -= pp;}

    //<effect name,<damage,effects>>
    std::unordered_map<string_std,std::tuple<int,int>> effects;
protected:
    double base_health = 150;
    double base_attack = 10;
    double crit_chance = 10;
    double crit_multiplier = 0.15;
    double base_shield = 150;
    int PP_points = 20;
    float armor_hit_percent = 0.35;

    Character_moves* player_moves;
    //<string name, tuple<Move class ,how many moves the effect has left>>
};

//child class of Chracter
class Wizard : public Character{
public:
    Wizard();

    // void attack(Character* other) override;
};

class Mage : public Character{
public:
    Mage();

    // void attack(Character* other) override;
};


// //child class of Chracter
// class Knight : public Character{
// public:
//     Knight();
//     void select_moves() override;
//     void attack(Character* other) override;
//     void choose_computer_attacks() override;
// };

// //child class of Chracter
// class Dragon : public Character{
// public:
//     Dragon();
//     void select_moves() override;
//     void attack(Character* other) override;
//     void choose_computer_attacks() override;
// };

// //child class of Chracter
// class Goblin : public Character{
// public:
//     Goblin();
//     void select_moves() override;
//     void attack(Character* other) override;
//     void choose_computer_attacks() override;
// };

#endif