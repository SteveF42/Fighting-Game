/*
    Filename moves.cpp
    description: declares the base class "Move" and "Character_Move" functions
*/
#include"moves.h"

/*
    =====================================
    Class Move Function
    =====================================
*/

void Move::display_stats(){
    std::cout << "Name: " << this->name << '\n';
    std::cout << "Description: " << this->description << '\n';
    std::cout << "Damage: " << this->damage << '\n';
    std::cout << "PP Cost: " << this->PP_cost << '\n';
}

void Move::apply_attack_to_player(Character* player, Character* other){
    system("clear");
    std::cout << this->display_message_on_attack << '\n';
    player->update_pp(this->PP_cost);
}
double Move::calculate_total_damage(Character* player){
    bool is_crit = player->calculate_crit_chance();
    double crit_multiplyer = player->get_crit_multiplier();
    double total_damage = this->damage + player->get_base_attack();
    total_damage +=  is_crit ? (total_damage * crit_multiplyer) : 0;
    return total_damage;
}
double Move::calculate_armor_damage(Character* other,double current_damage){
    double armor_hit = other->get_armor_hit_percent();
    double armor_damage = current_damage * armor_hit;
    return armor_damage;
}

bool Move::calculate_special_chance(double chance_num){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> range(0,100);
    double rand_int = range(mt);
    bool is_special = rand_int < chance_num;
    return is_special;
}



/*
    =====================================
    Class Character_moves Function
    =====================================
*/

Move* Character_moves::select_move(){
    Move* selected_move = nullptr;
    while(true){
        display_chosen_moves();
        std::cout << "\nPlease select an attack: ";
        int input;
        std::cin >> input;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid Input\n";
            continue;
        }
        
        selected_move = player_moves[input-1];
        break;
    }
    return selected_move;
}

void Character_moves::choose_moves(){
    //only hold 4 attacks
    while(player_moves.size()<4 && !player_moves.empty()){
        system("clear");
        show_possible_moves();

        std::cout << "Please select a move: ";
        int choice;
        std::cin >> choice;
        if(std::cin.fail()) {std::cin.clear(); std::cin.ignore();std::cout << "Invalid input\n"; continue;}

        player_moves.push_back(all_choices[choice-1]);
        all_choices.erase(all_choices.begin()+choice-1);
    }
}


void Character_moves::display_chosen_moves(){
    std::cout << "\n\n";
    for (int i = 0; i < player_moves.size();i++)
    {
        std::cout << i+1 << ".)\n";
        player_moves[i]->display_stats();
    }
}

void Character_moves::show_possible_moves(){
    for (int i = 0; i < all_choices.size();i++)
    {
        std::cout << i+1 << ".)\n";
        all_choices[i]->display_stats();
    }
}

Character_moves::~Character_moves(){
    std::cout << "I'm being DESTROYED!!!";
    for (auto &i : all_choices)
    {
        delete i;
    }
    for (auto &i : player_moves)
    {
        delete i;
    }
    player_moves.clear();
    all_choices.clear();
}