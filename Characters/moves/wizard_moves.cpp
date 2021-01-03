/*
    Filename wizard_moves.cpp
    description: Implements all of the moves for the wizard class
*/
#include"moves.h"
#include"windows.h"
#include"cmath"
/*
    ================================================
    WIZARD MOVE CHOICES
    ================================================
*/


class DarkCast : public Move{
public:
    DarkCast(){
        this->damage = 0;
        this->description = "Cast a mystical potion that lowers your opponents attack damage!";
        this->name = "Dark Cast";
        this->PP_cost = 5; 
        this->display_message_on_attack = "A dark shroud weakens your enemy lowering their attack by " + std::to_string(this->lower_attack_points)+" pts!";
    }
    void display_stats() override{
        Move::display_stats();
        std::cout << "Lowers opponents damage by " << lower_attack_points << '\n';
    }
    void apply_attack_to_player(Character* player,Character* other) override{
        Move::apply_attack_to_player(player,other);
        //lowers enemy player attack 
        other->update_player_stats(0,-(this->lower_attack_points),0,0,0);
        
    }
private:
    int lower_attack_points = 6.3;
};


class LightningShock : public Move{
public:
    LightningShock(){
        this->name = "Lightning Shock";
        this->damage = 14;
        this->description = "Release a lightning spell that shocks your opponent (chance to stun)";
        this->PP_cost = 4;
        this->display_message_on_attack = "A large bolt of lightning was released";
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
        bool is_stun = calculate_special_chance(stun_chance);
        if(is_stun){
            std::cout << "You have been Stunned!\n";
            other->effects.insert({stun_msg,{stun_damage,damage_duration}});
        }
    }
private:
    int damage_duration = 1; //moves
    double stun_damage = 3;
    string_std stun_msg = "Stun";
    double stun_chance = 25;
    
};

class PoisonShroud : public Move{
public:
    PoisonShroud(){
        this->name = "PoisonShroud";
        this->damage = 10;
        this->description = "Toxic attack which hurts your opponent (chance of poisoning)";
        this->PP_cost = 5;
        this->display_message_on_attack = "A poisonous mist was released!"; 
    }
    void display_stats() override{
        Move::display_stats();
        std::cout << "Poison damage: 3pts per turn\n";
    } 
    void apply_attack_to_player(Character* player,Character* other) override{
        Move::apply_attack_to_player(player,other);
        double total_damage = this->calculate_total_damage(player) + this->damage;
        double armor_damage = this->calculate_armor_damage(other,total_damage);
        total_damage -= armor_damage;
        //use negative number when updating player stats
        total_damage = std::max(0.0,total_damage);
        armor_damage = std::max(0.0,armor_damage);

        std::cout << "Opponent received -" << total_damage << " health, -" << armor_damage <<" armor!\n";
        other->update_player_stats(-total_damage,0,-armor_damage,0,0);
        bool is_poison = this->calculate_special_chance(poison_chance);
        //do something with the poison chance, idk how but do it
        if(is_poison){
            std::cout << "You have been poisoned!\n";
            other->effects.insert({poison_msg,{poison_damage,damage_duration}});
        }
        
    }

private:
    int damage_duration = 3; //moves
    double poison_damage = 3;
    string_std poison_msg = "Poison";
    double poison_chance = 15;
};

class StaffCharge : public Move{
public:
    StaffCharge(){
        this->name = "Staff Shroud";
        this->damage = 0;
        this->description = "Charge up your special staff and increase base attack";
        this->PP_cost = 3;
        this->display_message_on_attack = "Your attack stat has increased by " + std::to_string(this->damage_boost)+ " points!"; 
    }
    void display_stats() override{
        Move::display_stats();
        std::cout << "Damage Boost: 4\n";
    } 

    void apply_attack_to_player(Character* player,Character* other) override{
        Move::apply_attack_to_player(player,other);
        player->update_player_stats(0,damage_boost,0,0,0);
        
    }
private:
    int damage_boost = 5.3;
};

class PotionOfHealing : public Move{
public:
    PotionOfHealing(){
        this->name = "Potion Of Healing";
        this->damage = 0;
        this->description = "Drink a magical potion that restores shield and Health!";
        this->PP_cost = 4;
        this->display_message_on_attack = "Potion of Healing has been used!"; 
    }
    void display_stats() override{
        Move::display_stats();
        std::cout << "Healing Points: +" << restore_health_points <<" pts\n";
        std::cout << "Shield Points: +"<< restore_shield_points << " pts\n";
    } 

    void apply_attack_to_player(Character* player,Character* other) override{
        //negative is technically adding it since the base subtracts
        Move::apply_attack_to_player(player,other);
        player->update_player_stats(restore_health_points,0,restore_shield_points,0,0);
        std::cout << "Health Restored: " << this->restore_health_points << ", Armor restored: " << this->restore_shield_points << '\n';
        
    }
private:
    double restore_shield_points = 12;
    double restore_health_points = 25;
};

class BaseWizardMove : public Move{
public:
    BaseWizardMove(){
        this->name = "Dark Orb";
        this->damage = 10;
        this->description = "Release a mysterious element from the magica Orb.";
        this->PP_cost = 5;
        this->display_message_on_attack = "You used dark VooDoo Magic!"; 
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
    }
private:
};

/*
    ============================================
    WIZARD CLASS CODE
    ============================================
*/

Wizard_moves::Wizard_moves(){
    //all player choices
    all_choices.push_back(new DarkCast);    
    all_choices.push_back(new PoisonShroud);
    all_choices.push_back(new LightningShock);
    all_choices.push_back(new StaffCharge);
    all_choices.push_back(new PotionOfHealing);

    //pushes one base move back
    player_moves.push_back(new BaseWizardMove);
}

