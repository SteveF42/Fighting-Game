#include"character.h"

void Character::select_moves(){
    this->player_moves->choose_moves();
}

void Character::choose_computer_attacks(){
    //do some random shit to choose computer attacks
}

void Character::update_player_stats(double health_stat, double attack_stat, double shield_stat, float crit_chance, double crit_multiplier)
{
    this->base_health += health_stat;
    this->base_attack += attack_stat;
    this->base_shield += shield_stat;
    this->crit_chance += crit_chance;
    this->crit_multiplier += crit_multiplier;
}
void Character::display_player_stats()
{
    std::cout << "Health: " << this->base_health << '\n';
    std::cout << "Attack: " << this->base_attack << '\n';
    std::cout << "Shield: " << this->base_shield << '\n';
    std::cout << "PP: " << this->PP_points << '\n';
}


bool Character::calculate_crit_chance()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> range(0, 100);
    double rand_int = range(mt);
    bool is_crit = rand_int < crit_chance;
    if (is_crit)
        std::cout << "ITS A CRITICAL HIT!\n";
    return is_crit;
}



void Character::attack(Character *other){
    std::cout << "\nOpponents stats\n";
    other->display_player_stats();

    //checks if the player has been effected with anything
    for(auto it = this->effects.begin(), next_it = it; it!= effects.end(); it=next_it){
        next_it++;

        const int damage = std::get<0>(it->second);
        int* turns_left = &std::get<1>(it->second);
        if(*turns_left > 0){
            std::cout << "\nYou have been affected with (" << it->first << ") effect, lasting " << *turns_left << " turn(s)!"<< '\n';
            *turns_left -= 1;
            this->base_health -= damage;

            if(it->first == "Stun" || it->first == "Frost" || it->first == "Cooldown"){
                std::cout << "Looks like Your're unable to move! Your turn is being skipped!\n";
                std::cout << "Press enter to continue... \n";
                std::cin.ignore();
                char c = std::cin.get();
                system("clear");
                return;
            }                
        }else{
            std::cout << it->first <<" Effects have worn off!\n";            
            effects.erase(it);
        }
    }

    std::cout << "\nCurrent player stats\n";
    this->display_player_stats();

    Move* selected_move = player_moves->select_move();
    if(this->PP_points <=0 || this->PP_points < selected_move->get_pp()){
        system("clear");
        std::cout << "NOT ENOUGH PP!\n";
        return;
    }
    selected_move->apply_attack_to_player(this,other);
}