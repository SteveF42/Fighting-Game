/*
    Filename wizard_moves.cpp
    description: Implements all of the moves for the wizard class
*/
#include"moves.h"
#include"windows.h"
#include"cmath"
#include<random>
/*
    ================================================
    WIZARD MOVE CHOICES
    ================================================
*/


class AbraCadabra : public Move{
public:
    AbraCadabra(){
        this->damage = 0;
        this->description = "Who knows what you might get????";
        this->name = "Abra Cadabra";
        this->PP_cost = 8; 
        this->display_message_on_attack = "?????????????";
    }
    void apply_attack_to_player(Character* player,Character* other) override{
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> range(0,100);
        int rand_int = range(mt);

        bool skip = false;
        if(rand_int < 5){
            this->damage = 50;
            this->display_message_on_attack = "MASSIVE DAMAGE!!!!!";
        }else if(rand_int < 18){
            this->damage = 0;
            this->display_message_on_attack = "You seem to have healed yourself!";
            player->update_player_stats(50,0,0,0,0);
            std::cout << "Health restored by 50 pts!\n";
            skip = true;
        }else if(rand_int < 30){
            this->display_message_on_attack = "Medium hitting attack.";
            this->damage = 20;
        }else if(rand_int < 45){
            this->display_message_on_attack = "You gave yourself a small buff!";
            this->damage = 0;
            player->update_player_stats(0,10,0,5,0);
            std::cout << "+10 Attack, +5 Crit Chance\n";
            skip = true;
        }else if(rand_int < 80){
            this->display_message_on_attack = "Weak attack.";
            this->damage = 5;
        }else{
            this->display_message_on_attack = "Your attack seemed to have missed?";
            this->damage = 0;
            skip = true;
        }
        Move::apply_attack_to_player(player,other);
        
        double total_damage = calculate_total_damage(player);
        double armor_damage = calculate_armor_damage(other,total_damage);
        total_damage -= armor_damage;

        total_damage = std::max(0.0,total_damage);
        armor_damage = std::max(0.0,armor_damage);
        
        //lowers enemy player attack 
        if(!skip){
            other->update_player_stats(-total_damage,0,-armor_damage,0,0);
            std::cout << "Opponent received -" << total_damage << " health, -" << armor_damage <<" armor!\n";
        }

    }
private:

};


class Blizzard : public Move{
public:
    Blizzard(){
        this->name = "Blizzard";
        this->damage = 25;
        this->description = "Release A sub zero Blizzard which can potentially freeze them in place!";
        this->PP_cost = 8;
        this->display_message_on_attack = "A raging Blizzard approaches!";
    }
    void apply_attack_to_player(Character* player,Character* other) override{
        Move::apply_attack_to_player(player,other);
        double total_damage = this->calculate_total_damage(player);
        double armor_damage = this->calculate_armor_damage(other,total_damage);
        
        total_damage -= armor_damage;
        total_damage = std::max(0.0,total_damage);
        armor_damage = std::max(0.0,armor_damage);
        //use negative number when updating player stats
        std::cout << "Opponent received -" << total_damage << " health, -" << armor_damage <<" armor!\n";
        other->update_player_stats(-total_damage,0,-armor_damage,0,0);
        bool is_stun = calculate_special_chance(freeze_chance);
        if(is_stun){
            std::cout << "You have become frozen!\n";
            other->effects.insert({stun_msg,{stun_damage,damage_duration}});
        }

    }
private:
    int damage_duration = 1; //moves
    double stun_damage = 3;
    string_std stun_msg = "Frost";
    double freeze_chance = 15;
    
};

class BlackMagic : public Move{
public:
    BlackMagic(){
        this->name = "Black Magic";
        this->damage = 0;
        this->description = "Curse your opponent with a Dark spell which lowers attack and shield stat!";
        this->PP_cost = 5;
        this->display_message_on_attack = "A poisonous mist was released!"; 
    }
    void display_stats() override{
        Move::display_stats();
        std::cout << "Lower shield stat: -" << lower_shield_stat << " pts, Lower attack stat: -" <<lower_attack_stat <<" pts\n";
    } 
    void apply_attack_to_player(Character* player,Character* other) override{
        Move::apply_attack_to_player(player,other);
        std::cout << "Lowered opponents stats by -" << lower_attack_stat << " attack, -" << lower_shield_stat <<" armor!\n";
        other->update_player_stats(0,lower_attack_stat,lower_shield_stat,0,0);
        //do something with the poison chance, idk how but do it        
    }

private:
    double lower_attack_stat = 7;
    double lower_shield_stat = 25;
};

class DemonPower : public Move{
public:
    DemonPower(){
        this->name = "Demon Power";
        this->damage = 0;
        this->description = "Sumon the demons and harness the power of darkness! Lowers crit chance immensly and raises Attack dmg immensly!";
        this->PP_cost = 3;
        this->display_message_on_attack = "Your attack stat has increased by " + std::to_string(this->damage_boost)+ " points!"; 
    }
    void display_stats() override{
        Move::display_stats();
        std::cout << "Damage Boost: "<< damage_boost << "Crit Chance: -"<< crit_chance << "\n";
    } 

    void apply_attack_to_player(Character* player,Character* other) override{
        Move::apply_attack_to_player(player,other);

     
    }
private:
    double damage_boost = 20;
    double crit_chance = 20;

};

class SummonTheGods : public Move{
public:
    SummonTheGods(){
        this->name = "Summon The Gods";
        this->damage = 50;
        this->description = "Gain the power of the Gods and release an ultra attack! (miss an attack for one round)";
        this->PP_cost = 15;
        this->display_message_on_attack = "The Gods have given immense power!"; 
    }
    void display_stats() override{
        Move::display_stats();
    } 

    void apply_attack_to_player(Character* player,Character* other) override{
        //negative is technically adding it since the base subtracts
        Move::apply_attack_to_player(player,other);
        double total_damage = this->calculate_total_damage(player) + this->damage;
        double armor_damage = this->calculate_armor_damage(other,total_damage);
        total_damage -= armor_damage;
        //use negative number when updating player stats
        total_damage = std::max(0.0,total_damage);
        armor_damage = std::max(0.0,armor_damage);

        std::cout << "Opponent received -" << total_damage << " health, -" << armor_damage <<" armor!\n";
        other->update_player_stats(-total_damage,0,-armor_damage,0,0);

        player->effects.insert({msg,{0,cool_down_rounds}});
    }
private:
    int cool_down_rounds = 2;
    string_std msg = "Cooldown";
};

class BaseMageMove : public Move{
public:
    BaseMageMove(){
        this->name = "Ice Mist";
        this->damage = 0;
        this->description = "Summon a cloud which lowers opponents crit chance with a chance of hitting them with ice!";
        this->PP_cost = 5;
        this->display_message_on_attack = "A shroud of mist covers the erena!"; 
    }
    void display_stats() override{
        std::cout << "Ice damage: " << ice_damage << "\n";
    }
    void apply_attack_to_player(Character* player,Character* other) override{
        Move::apply_attack_to_player(player,other);

        double total_damage = 0;

        bool isIceHit = this->calculate_special_chance(ice_chance);
        if(isIceHit){
            std::cout << "You have been pelted by ice! -" << ice_damage << '\n';
            total_damage = ice_damage;    
        }
        //use negative number when updating player stats
        std::cout << "Opponent received - " << lower_crit << " Crit Chance!\n";
        other->update_player_stats(-total_damage,0,0,-lower_crit,0);
    }
private:
    double ice_chance = 10;
    double lower_crit = 0.10;
    double ice_damage = 12;
};

/*
    ============================================
    WIZARD CLASS CODE
    ============================================
*/

Mage_moves::Mage_moves(){
    //all player choices
    all_choices.push_back(new AbraCadabra);    
    all_choices.push_back(new BlackMagic);
    all_choices.push_back(new Blizzard);
    all_choices.push_back(new DemonPower);
    all_choices.push_back(new SummonTheGods);

    //pushes one base move back
    player_moves.push_back(new BaseMageMove);
}

